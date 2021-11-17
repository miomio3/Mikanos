sudo mount -o loop disk.img mnt
sudo mkdir -p mnt/EFI/BOOT
sudo cp /mnt/c/Users/uj132/edk2/Build/MikanLoaderX64/DEBUG_CLANG38/X64/Loader.efi mnt/EFI/BOOT/BOOTX64.EFI
sudo cp ../kernel/kernel.elf mnt/kernel.elf
sudo umount mnt
qemu-system-x86_64\
 -drive if=pflash,format=raw,readonly,file=/mnt/c/Users/uj132/programming_win/mikanos/uchan-os-build/devenv/OVMF_CODE.fd \
 -drive if=pflash,format=raw,file=/mnt/c/Users/uj132/programming_win/mikanos/uchan-os-build/devenv/OVMF_VARS.fd \
 -drive if=ide,index=0,media=disk,format=raw,file=disk.img \
 -device nec-usb-xhci,id=xhci \
 -device usb-mouse -device usb-kbd \
 -monitor stdio 
