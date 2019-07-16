# ottsm osm backend
export PATH="$HOME/.rbenv/bin:$PATH"
eval "$(rbenv init -)"

# Git aliases
alias gst='git status'
alias gau="git add -u"
alias gdff='git diff'
alias gcm='git commit -m'
alias gca='git commit --amend --no-edit'
alias gcae='git commit --amend'
alias gps='git push'
alias gpso='git push origin'
alias gpl='git pull'
alias grb='git rebase'
alias grbm='git rebase master'

alias gco='git checkout'
alias gcom='git checkout master'
alias gco-='git checkout -'
# More here: https://dev.to/robertcoopercode/using-aliases-to-speed-up-your-git-workflow-2f5a
# And here: https://gist.github.com/sdeering/8437725

# Aliases for rails projects
alias rake='bundle exec rake'
alias rails='bundle exec rails'
alias rspec='bundle exec rspec'
alias renv='RAILS_ENV'

export RAILS_LOGGER='default'
