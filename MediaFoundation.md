# Developing Microsoft Media Foundation Applications

## Core Media Foundation Concepts

In a media pipeline, the output of the upstream components is used as the input for some downstream components, and no chain of components contains a loop. When dealing with MF objects, you can also call the pipeline a graph or a topology.

MF sources: These are the components that load the multiplexed data streams from a file or the network, unpack the elementary audio and video streams from the container, and send them to other objects in the topology.

Media Foundation transforms(MFTs): These are components that transform the data in various way.

MF sinks: These components are responsible for rendering content on the screen or to the audio card, saving data to the hard drive, or sending it over the network.

An MF media type object describes the type of media in a data stream that is produced or consumed by an MF component. A media type contains several values that define the data type that an MF component can produce or consume.

Mayjor type: Define the generic type of data handled by a component. For example, it cna be audio, vidoe, closed captioning, or custom iTV data.

Subtype: Indicates the specific format of the data. Usually this value indicates the compression used in the data stream, such as MP3, MPEG2 or H264.

Beside these values, a media type can also contain any number of custom data structures and parameters with specific information required to decode the data.

Each media sample is an object with a data buffer, with a small segment of the data stream and a set of information describing the data.

Each sample object is essentially a wrapper around the internal buffer object. To improve performance and speed up allocations, MF reuses the data buffers.

To build an MF media pipeline, an MF topology, applications usually use the MF topology builder components provided with Windows.


## TopoEdit

Topology nodes are a level of abstraction above the MF objects. With topology nodes, you can control how the actual objects are created without having to instantiate the actual objects directly.

## Media Playback

Topology is used to initialize and connect the MPH objects that are actually responsible for processing media data.

The media session holds all of the MPH components that process the data and gives you the ability to start and stop playback. During playback, the media session pulls samples from the source, passes them through the MFRS, and sends them to the renderer's.

Windows applications do  not execute on a single thread. Instead, they have a message loop that constantly waits for events and performs different actions based on the event information.

After a media session is created, you need to specify a callback object(IMFAsyncCallback interfacethat) will receive asynchronous events from the session. You do that try calling the IMFMediaEventGenerator::BeginGetEvent() function, which notifies the media event generator(the media session) that the next events should be sent to the passed-in object.

Event generator(session) calls IMFAsyncCallback::Invoke() to notify the event handler of a new event in the queue.

The event handler calls the event generator back and gets the actual event from the queue with the IMFMediaEventGenerator::EndGetEvent() method.

MF functions do not directly execute any operations; instead, the calls only schedule the work with the main object, and return immediately. The work items themselves then execute on a background thread. After the work is completed, the objects fire events that notify the caller of the status of the scheduled work item. To facilitate this asynchronous communication system, the media session receives a pointer to an event callback object. This callback object will be called whenever something of note happens.

If the IMFMediaEvent object was fired because of a failure, the HRESULT stored in the event object will indicate what sort of failure that it. To get the failing HRESULT, use hte IMFMediaEvent::GetStatus() method.

Topology-building steps:
+ Get the presentation descriptor from the source.
+ Get a steam descriptor from the presentation descriptor.
+ Create the source node for the stream descriptor
+ Create the sink node of the right media type for this stream.
+ Connect the source and sink nodes to each other.
+ If there are streams left to process, go back to step 2.



```
hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

hr = MFStartup(MF_VERSION);
        
m_closeCompleteEvent = CreateEvent(NULL, FALSE, FALSE, NULL);

hr = MFCreateMediaSession(NULL, &m_pSession);

hr = m_pSession->BeginGetEvent((IMFAsyncCallback*)this, NULL);

hr = m_pSession->SetTopology(0, pTopology);

hr = m_pSession->EndGetEvent(pAsyncResult, &pEvent);

hr = m_pSession->BeginGetEvent(this, NULL);

hr = pMediaEvent->GetType(&eventType);

hr = pMediaEvent->GetStatus(&hrStatus);

if(eventType == MESessionTopologyStatus)
{
    hr = pMediaEvent->GetUINT32(MF_EVENT_TOPOLOGY_STATUS, (UINT32*)&TopoStatus);
}
else if (eventType == MESessionClosed)
{
    SetEvent(m_closeCompleteEvent);
}

hr = MFGetService(m_pSession, MR_VIDEO_RENDER_SERVICE,  IID_IMFVideoDisplayControl, (void**)&m_pVideoDisplay);
                
hr = m_pSession->Start(&GUID_NULL, &varStart);

hr = MFCreateSourceResolver(&pSourceResolver);

hr = pSourceResolver->CreateObjectFromURL(sURL,
    MF_RESOLUTION_MEDIASOURCE | MF_RESOLUTION_CONTENT_DOES_NOT_HAVE_TO_MATCH_EXTENSION_OR_MIME_TYPE,  
    NULL, &objectType, &pSource);

hr = MFCreateTopology(&m_pTopology);

hr = m_pSource->CreatePresentationDescriptor(&pPresDescriptor);

hr = pPresDescriptor->GetStreamDescriptorCount(&nSourceStreams);

hr = pPresDescriptor->GetStreamDescriptorByIndex(nStream, &streamSelected, &pStreamDescriptor);
            
hr = MFCreateTopologyNode(MF_TOPOLOGY_SOURCESTREAM_NODE, &pNode);

hr = pNode->SetUnknown(MF_TOPONODE_SOURCE, m_pSource);

hr = pNode->SetUnknown(MF_TOPONODE_PRESENTATION_DESCRIPTOR, pPresDescriptor);

hr = pNode->SetUnknown(MF_TOPONODE_STREAM_DESCRIPTOR, pStreamDescriptor);

hr = pStreamDescriptor->GetMediaTypeHandler(&pHandler);

hr = pHandler->GetMajorType(&majorType);

hr = MFCreateVideoRendererActivate(hwndVideo, &pRendererActivate);

hr = MFCreateTopologyNode(MF_TOPOLOGY_OUTPUT_NODE, &pNode);

hr = pNode->SetObject(pRendererActivate);

hr = m_pTopology->AddNode(pSourceNode);

hr = m_pTopology->AddNode(pOutputNode);

hr = pSourceNode->ConnectOutput(0, pOutputNode, 0);

hr = m_pSource->Shutdown();
        
m_pSource.Release();

hr = m_pSession->Close();

m_pSession->Shutdown();

dwWaitResult = WaitForSingleObject(m_closeCompleteEvent, 5000);
                
MFShutdown();

CoUninitialize();

CloseHandle(m_closeCompleteEvent);

```

## Transcoding

Transcoding refers to transforming an existing video or audio stream from one format to another.

source -> decoder -> encoder -> sink

### The transcode API

The transcode API was introduce to simplify the job of building a transcoding topology. This API automates the most common tasks -- selection of the right combination of decoders and encoders needed to transcode a file.

Transcode profile contains the transcoding parameters.

## Media Foundation Transforms


## Media Foundation Sources


## Media Foundation Sinks


## Custom Media Sessions


## Advanced Media Foundation Topics


## Debugging Media Foundation Code


## COM concepts


## Active Template Library Objects


