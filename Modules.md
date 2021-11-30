* commands:
insmod

rmmod

modprobe

depmod

* files:
/lib/modules

/proc/modules

The module dependency information is stored in the file /lib/modules/version/modules.dep

module_param(name, type, perm);

[hello.c](hello.c)

[hello_makefile](hello_makefile)

$insmod hello.ko
$rmmod hello

