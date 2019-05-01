#!/bin/sh
timedatectl set-ntp true
echo -e "n\np\n\n\n\nw" | fdisk /dev/sda
mkfs.ext4 /dev/sda1
mount /dev/sda1 /mnt
sed -i 's,arch.mirror.constant.com,mirror.isoc.org.il/pub/archlinux,g' /etc/pacman.d/mirrorlist
pacstrap /mnt base grub sudo bash-completion linux-headers xorg-fonts-100dpi xorg-server xorg-apps lxde ttf-dejavu virtualbox-guest-utils
genfstab -U /mnt >> /mnt/etc/fstab  
arch-chroot /mnt grub-install --target=i386-pc /dev/sda 
arch-chroot /mnt grub-mkconfig -o /boot/grub/grub.cfg 
arch-chroot /mnt ln -sf /usr/share/zoneinfo/Asia/Jerusalem /etc/localtime 
arch-chroot /mnt hwclock --systohc
arch-chroot /mnt useradd -m -G wheel,video,audio vm
echo -e 'a\na' | arch-chroot /mnt passwd vm
arch-chroot /mnt sed -i 's,#en_US.UTF-8,en_US.UTF-8,g' /etc/locale.gen 
arch-chroot /mnt locale-gen
echo 'LANG=en_US.UTF-8' > /mnt/etc/locale.conf
echo 'a' > /mnt/etc/hostname
arch-chroot /mnt systemctl enable dhcpcd
arch-chroot /mnt systemctl enable lxdm
arch-chroot /mnt sed -i 's,# %wheel ALL=(ALL) ALL,%wheel ALL=(ALL) ALL,g' /etc/sudoers 
echo -e 'pacman -S --noconfirm --needed base-devel git && cd /home/vm && sudo -u vm git clone https://aur.archlinux.org/trizen.git && cd trizen && sudo -u vm makepkg -s && pacman -U --noconfirm  *.pkg.tar.xz && cd /home/vm && rm -rf trizen' > b
mv b /mnt
arch-chroot /mnt sh b
rm /mnt/b
reboot
#My Synths are consisted of 3 procecing units:
#The first one being the neural system. It's a specialized system, almost no programing, you know the deal. /dev/nrl
#The second one is the "API". It directly manages the neural system, all sensory info goes to the neural system to it. 
#The stock API directly sends sensory info to the nrl. The stock API is only mammal like so you can't do wings and such but there are easily available apis that allow for that.
#It can directly oporate a synth chassis, however it's usually not done if the third PU is not broken. It can disconnect the third PU in cases of emergency (E.G viruses).
#It manages the nanites and templates.
#The OS it runs is mounted as ro. You can dd an image to it in order to change it.
#The third one is "User accecible" computer. It has the semi external ports, it can be upgraded, and it originally didn't come in. It's the computer that uses the API to provide all the simulations to the nrl, all the chassis to the nrl, etc... . If a Synth installs a program on themselves they install it here. It can run anything you want, most OSs have compatibilty packages (You may want an RTOS - not exactly sure of the imlications).
