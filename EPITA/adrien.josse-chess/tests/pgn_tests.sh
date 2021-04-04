#!/bin/bash
for file in $(echo ../tests/given_pgn/*.pgn)
do

    name="$(echo "$file" | cut -d "." -f 3)"
    name="$(echo "$name" | cut -d "/" -f 4)"

    ./chessengine --pgn ../tests/given_pgn/$name.pgn -l ../tests/libbasic-output.so > pgn_tmp 2> /dev/null

    d="$(diff pgn_tmp "../tests/given_pgn/$name.out")"
    if [ -n "$d" ]; then
        echo "$name"
        echo "$d"
        echo
    fi
done

rm pgn_tmp

exit 0
