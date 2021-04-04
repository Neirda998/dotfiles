cur_dir="$(dirname ${BASH_SOURCE[0]})"

if [ "$1" = "clean" ]; then
    echo "Setting up env. . ."
    rm -r "${cur_dir}/42sh_env"
    exit 0
fi

need_install=0
if [ ! -d "${cur_dir}/42sh_env" ]; then
    need_install=420
    python -m venv "${cur_dir}/42sh_env/" &
    pid="$!"
    echo -n "Creating env"
    while $(kill -0 $pid 2> /dev/null)
    do
        echo -ne " ."
        sleep 0.7
    done
    echo " OK"
fi

source "${cur_dir}/42sh_env/bin/activate"

if [ "${need_install}" -eq 420 ]; then
    pip install -r "${cur_dir}/requirements.txt"
fi

python "${cur_dir}/test_suite.py" "${cur_dir}/../../build/42sh"
deactivate

if [ "$1" = "all" ] && [ "$2" = "clean" ]; then
    rm -r "${cur_dir}/42sh_env"
    exit 0
fi
