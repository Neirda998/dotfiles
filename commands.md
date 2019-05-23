# List of commands and documentation

## Linux commands
### Word count `wc`
After a listing command (cat included), can add `| wc` to list a word cound\
Return 3 numbers that can be passed as option for command (can pass various).\
`cat [FILE] | wc`\
return `[-l for LINES] [-w for WORDS] [-c CHARACTERS]`

## Grep commands
`grep [OPTIONS] [SEARCH] [FILES]`

search in a git file:\
`git grep [SEARCH]`\
print line:\
`grep -n [SEARCH]`\
print lines below match:\
`grep -A [NUM] [SEARCH]`

## Ack commands
`ack [OPTIONS] [SEARCH] [FILES]`

print lines below match:\
`ack -A [NUM] [SEARCH]`

## Vim commands
