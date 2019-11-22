# Prompt display
#COLOR_BLACK="\033[0;30m"
#COLOR_RED="\033[0;31m"
#COLOR_GREEN="\033[0;32m"
#COLOR_BROWN="\033[0;33m"
#COLOR_BLUE="\033[0;34m"
#COLOR_PURPLE="\033[0;35m"
COLOR_CYAN="\033[0;36m"
COLOR_LIGHT_GREY="\033[0;37m"
#COLOR_DARK_GREY="\033[1;30m"
#COLOR_LIGHT_RED="\033[1;31m"
#COLOR_LIGHT_GREEN="\033[1;32m"
#COLOR_YELLOW="\033[1;33m"
#COLOR_LIGHT_BLUE="\033[1;34m"
#COLOR_LIGHT_PURPLE="\033[1;35m"
#COLOR_LIGHT_CYAN="\033[1;36m"
parse_git_branch() {
    git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/ (\1)/'
}
export PS1="\[$COLOR_WHITE\][\W]\[$COLOR_CYAN\]\$(parse_git_branch)\[$COLOR_LIGHT_GREY\]$ "
# Old basic prompt
# PS1='[\u@\h \W]\$ '

alias ls='ls --color=auto'

# Aliases
alias cl='clear'
alias la='ls -la'
# interesting stuff working on arch
alias lp='ls Makefile TODO README src src/include tests'
alias grepc='grep --color=auto -nr'
alias i3lock='i3lock --image=/home/adrien.josse/afs/Pics/PROJEEET.PNG'

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
# More here: https://dev.to/robertcoopercode/using-aliases-to-speed-up-your-git-workflow-2f5a
# And here: https://gist.github.com/sdeering/8437725

# SSH alias for git
alias gsa='ssh-add'

# Aliases for rails projects
alias rake='bundle exec rake'
alias rails='bundle exec rails'
alias rspec='bundle exec rspec'
alias renv='RAILS_ENV'

export RAILS_LOGGER='default'
