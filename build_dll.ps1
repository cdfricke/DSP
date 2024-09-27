<#
build_dll.ps1

boiler plate script that calls the correct g++ commands
in order to build a dll so I never forget

EX: For a header file called add.h with an implementation
file called add.cpp:
> g++ -c -o add.o add.cpp -D ADD_EXPORTS
> g++ -o add.dll add.o -s -shared
#>
$lib_name = "DSP"
$fobj = $lib_name + ".o"
$fimpl = $lib_name + ".cpp"
$fdll = $lib_name + ".dll"

# Don't forget to change the -D macro!
g++ -c -o $fobj $fimpl -D DSP_EXPORTS
g++ -o $fdll $fobj -s -shared