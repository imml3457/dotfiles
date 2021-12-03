#! /usr/bin/env bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"


if [[ "$1" == "--install-zsh" ]]
then
    echo "installing zsh"

    sudo apt install zsh

    echo "installing curl"

    sudo apt install curl

    echo "installing oh-my-zsh"

    sh -c "$(curl -fsSL https://raw.githubusercontent.com/ohmyzsh/ohmyzsh/master/tools/install.sh)" "" --unattended

    echo "installing p10k"

    git clone --depth=1 https://github.com/romkatv/powerlevel10k.git ${ZSH_CUSTOM:-$HOME/.oh-my-zsh/custom}/themes/powerlevel10k

    chsh -s $(which zsh)
fi

echo "installing tmux config"

ln -sf $DIR/.tmux.conf $HOME/.tmux.conf

echo "installing yed files"

if [ -d "$HOME/.config/yed" ]
then
    ln -sf $DIR/yed/yedrc $HOME/.config/yed/yedrc
    ln -sf $DIR/yed/ypm_list $HOME/.config/yed/ypm_list
else
    echo ".config/yed does not exist"
fi

echo "installing zshrc"

ln -sf $DIR/.zshrc $HOME/.zshrc
