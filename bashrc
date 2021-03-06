# Auto generated by Manjaro
# Might not be the case for others distros
# # ex - archive extractor
# # usage: ex <file>
ex ()
{
  if [ -f $1 ] ; then
    case $1 in
      *.tar.bz2)   tar xjf $1   ;;
      *.tar.gz)    tar xzf $1   ;;
      *.bz2)       bunzip2 $1   ;;
      *.rar)       unrar x $1     ;;
      *.gz)        gunzip $1    ;;
      *.tar)       tar xf $1    ;;
      *.tbz2)      tar xjf $1   ;;
      *.tgz)       tar xzf $1   ;;
      *.zip)       unzip $1     ;;
      *.Z)         uncompress $1;;
      *.7z)        7z x $1      ;;
      *)           echo "'$1' cannot be extracted via ex()" ;;
    esac
  else
    echo "'$1' is not a valid file"
  fi
}

# Prompt display
COLOR_BLACK="\033[0;30m"
COLOR_RED="\033[0;31m"
COLOR_GREEN="\033[0;32m"
COLOR_BROWN="\033[0;33m"
COLOR_BLUE="\033[0;34m"
COLOR_PURPLE="\033[0;35m"
COLOR_CYAN="\033[0;36m"
COLOR_LIGHT_GREY="\033[0;37m"
COLOR_DARK_GREY="\033[1;30m"
COLOR_LIGHT_RED="\033[1;31m"
COLOR_LIGHT_GREEN="\033[1;32m"
COLOR_YELLOW="\033[1;33m"
COLOR_LIGHT_BLUE="\033[1;34m"
COLOR_LIGHT_PURPLE="\033[1;35m"
COLOR_LIGHT_CYAN="\033[1;36m"
COLOR_WHITE="\033[01;37m"
COLOR_RESET="\033[00m"
parse_git_branch() {
    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}
# export PS1="\[$COLOR_WHITE\][\W]\[$COLOR_CYAN\]\$(parse_git_branch)\[$COLOR_LIGHT_GREY\]$ "
export PS1="\[$COLOR_WHITE\][\W]\[$COLOR_LIGHT_GREY\]\$(parse_git_branch)\[$COLOR_RESET\]$ "
# Old basic prompt
# PS1='[\u@\h \W]\$ '

alias ls='ls --color=auto'

# Aliases
alias cl='clear'
alias l='ls -l'
alias la='ls -la'
alias diff='diff --color=auto'

alias cp="cp -i"                          # confirm before overwriting something
alias df='df -h'                          # human-readable sizes
alias free='free -m'                      # show sizes in MB
# interesting stuff working on arch
alias lp='ls Makefile TODO README src src/include tests'
alias grepc='grep --color=auto -nr'
alias i3lock='i3lock --image=/home/adrien.josse/afs/Pics/PROJEEET.PNG'

# pimp my neofetch
# alias turbo='neofetch --colors 6 15 14 5 7 15 --w3m ~/Pictures/Luchador-small.png --crop_mode normal --loop'

# Git aliases
alias gcl='git clone'
alias gst='git status'
alias ga='git add'
alias gau='git add -u'
alias gdff='git diff'
alias gsw='git show'
alias gcm='git commit -m'
alias gca='git commit --amend --no-edit'
alias gcae='git commit --amend'

alias gps='git push'
alias gpso='git push origin'
alias gpsm='git push origin master'

alias gtag='git tag -f -m "" -a'
alias gpstag='git push --tags'
alias yeet='git push; git push --tags'

alias gpl='git pull'
alias grb='git rebase'
alias grbm='git rebase master'
alias grbc='git rebase --continue'

alias glg='git log'
alias glgl='git log --oneline'
alias gcms='glg --all --grep'
alias glgs='glgl --all --grep'

alias gco='git checkout'
alias gcom='git checkout master'
alias gco-='git checkout -'
alias gbr='git branch'

alias gmg='git merge'
alias gsa='ssh-add'
# More here: https://dev.to/robertcoopercode/using-aliases-to-speed-up-your-git-workflow-2f5a
# And here: https://gist.github.com/sdeering/8437725

# EPITA gcc
# alias gccW='gcc -Wall -Wextra -Werror -std=c99 -pedantic'
# alias g++W='g++ -Wall -Wextra -Werror -pedantic -std=c++17'
# alias g++2a='g++ -Wall -Wextra -Werror -pedantic -std=c++2a'

# Aliases for rails projects
alias rake='bundle exec rake'
alias rails='bundle exec rails'
alias rspec='bundle exec rspec'
alias renv='RAILS_ENV'

export RAILS_LOGGER='default'
