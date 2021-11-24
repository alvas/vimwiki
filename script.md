* ssh without password
```
ssh -i alvasli.pem alvaslic@162.241.216.245

```

* scp copy file to server
```
if [ $# -lt 2 ]
then
    echo "usage: ./bhcp2.sh -f file_name -d server_dir"
    echo ""
else
    while [ -n "$1" ]; do
        case "$1" in
            -f)
                file_name=$2
                shift
                ;;
            -d)
                dir_name=$2
                shift
                ;;
        esac
        shift
    done
    scp -i alvasli.pem $file_name alvaslic@162.241.216.245:ftp/$dir_name/$file_name
fi

```
