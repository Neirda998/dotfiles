# ottsm osm backend
export PATH="$HOME/.rbenv/bin:$PATH"
eval "$(rbenv init -)"

# Aliases
alias cl='clear'
alias la='ls -la'
# interesting stuff working on arch
alias lp='ls Makefile TODO README src src/include tests'
alias grepc='grep --color=auto -nr'

# Git aliases
alias gcl='git clone'
alias gst='git status'
alias gau='git add -u'
alias ga='git add'
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

alias gmg='git merge'
# More here: https://dev.to/robertcoopercode/using-aliases-to-speed-up-your-git-workflow-2f5a
# And here: https://gist.github.com/sdeering/8437725

# Aliases for rails projects
alias rake='bundle exec rake'
alias rails='bundle exec rails'
alias rspec='bundle exec rspec'
alias renv='RAILS_ENV'

export RAILS_LOGGER='default'
