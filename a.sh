# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    a.sh                                               :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yrhandou <yrhandou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/21 01:29:49 by zmrabet           #+#    #+#              #
#    Updated: 2025/06/25 16:32:48 by yrhandou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#!/bin/bash

GREEN='\033[1;32m'
RED='\033[1;31m'
NC='\033[0m'
print_success() {
    echo -e "$GREEN$1 √$NC"
}

print_error() {
    echo -e "$RED$1 X$NC"
}

print_info() {
    echo -e "$GREEN$1$NC"
}

print_info "42 @zmrabet"

# Install Valgrind using homebrew
print_info "Installing Valgrind !"
print_info "......................"

brew tap LouisBrunner/valgrind > /dev/null 2>&1

# Modify valgrind.rb for macOS 10.14.6
MAC=$(sw_vers | awk 'NR==2{print $2}')
if [ $MAC == "10.14.6" ]; then
    FILE="$HOME/.brew/Library/Taps/louisbrunner/homebrew-valgrind/valgrind.rb"
    sed -i '.bak' '/libtool/d' $FILE
fi

# Install valgrind
HOMEBREW_NO_AUTO_UPDATE=1 brew install --HEAD LouisBrunner/valgrind/valgrind
[ $? -eq 0 ] && print_success "Valgrind installed successfully" || print_error "Failed to install Valgrind"

# Restart shell
exec zsh
