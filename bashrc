# ottsm osm backend
export PATH="$HOME/.rbenv/bin:$PATH"
eval "$(rbenv init -)"

# Git aliases
alias gcm='git commit -m'
alias gca='git commit --amend --no-edit'
alias gcae='git commit --amend'

alias gco='git checkout'
# More here: https://dev.to/robertcoopercode/using-aliases-to-speed-up-your-git-workflow-2f5a
# And here: https://gist.github.com/sdeering/8437725

# Aliases for rails projects
alias rake='bundle exec rake'
alias rails='bundle exec rails'
alias rspec='bundle exec rspec'
alias renv='RAILS_ENV'

export RAILS_LOGGER='default'
