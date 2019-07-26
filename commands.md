# List of commands and documentation

## Linux commands
### Reload sources
Reload bash:\
`source ~/.bashrc` or `. ~/.bashrc`

Reload i3/config:\
$mod+shift+c

### Word count `wc`
After a listing command (ls, cat, ack, grep, etc), can add `| wc` to list a word cound\
Return 3 numbers that can be passed as option for command (can pass various, but will always be print in the same order).\
`cat [FILE] | wc`\
return `[-l for LINES] [-w for WORDS] [-c CHARACTERS]`

## Grep commands
`grep [OPTIONS] [SEARCH] [FILES]`

search in a git file:\
`git grep [SEARCH]`\
print line:\
`grep -n [SEARCH]`\
print lines below match:\
`grep -A [NUM] [SEARCH]`\
print lines before match:\
`grep -B [NUM] [SEARCH]`\
print lines before and below match:\
`grep -C [NUM] [SEARCH]`

## Ack commands
In most of the cases, ack commands work in the same way as grep commands. Ack is just a little quicker.\
`ack [OPTIONS] [SEARCH] [FILES]`

print lines below match:\
`ack -A [NUM] [SEARCH]`\
print lines before match:\
`grep -B [NUM] [SEARCH]`\
print lines before and below match:\
`grep -C [NUM] [SEARCH]`\
default is 2

## Vim commands
### Substitution
`:%s/txt/new_txt/g`\
Add `c` at the end for confirmation
