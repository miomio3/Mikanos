sudo mount -o loop disk.img mnt
sudo cp $1 mnt/EFI/BOOT/BOOTX64.EFI
sudo umount mnt
qemu-system-x86_64 -drive if=pflash,file=$HOME/osbook/devenv/OVMF_CODE.fd -drive if=pflash,file=$HOME/osbook/devenv/OVMF_VARS.fd -hda disk.img 
