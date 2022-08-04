#! /usr/bin/env bash

DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
yed_dir=$HOME/.config/yed

CMD_ARRAY=("--help" "--install-zsh" "--no_zshrc" "--force")

if [[ "$1" == ${CMD_ARRAY[0]} ]]
then
    for i in ${CMD_ARRAY[@]}
    do
        printf "COMMAND: %s\n" $i
    done
    exit 1
fi

if [[ "$1" == ${CMD_ARRAY[1]} ]]
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

if [ ! -L "$yed_dir" ]
then
    echo "installing yed files"
    ln -sf $DIR/yed $HOME/.config/yed
    cd yed
    ./update.sh
    cd ../
elif [[ "$1" == ${CMD_ARRAY[3]} ]]
then
    echo "reinstalling yed"
    rm -rf $HOME/.config/yed
    ln -sf $DIR/yed $HOME/.config/yed
    cd yed
    ./update.sh
    cd ../
fi

if [[ "$1" != ${CMD_ARRAY[2]} ]]
then
    echo "installing zshrc"
    ln -sf $DIR/.zshrc $HOME/.zshrc
fi
