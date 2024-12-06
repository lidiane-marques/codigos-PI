#!/bin/bash

# Função para exibir ajuda
function help() {
    echo "-----------------HELP---------------------------------"
    echo
    echo "Parâmetros:"
    echo "  -l    Linguagem de programação (python ou c)"
    echo "  -a    Algoritmo de ordenação (bubble ou merge)"
    echo "  -n    Número de execuções"
    echo "  -t    Tamanhos das entradas separados por vírgula"
    echo "  -g    Gerar grafico de comparação"
    echo "-----------------------------------------------------"
    exit 1
}


input_sizes=()
graph=false

while getopts "l:a:n:t:g" opt; do
    case $opt in
        l) language=$OPTARG ;;
        a) algorithm=$OPTARG ;;
        n) num_executions=$OPTARG ;;
        t) IFS=',' read -r -a input_sizes <<< "$OPTARG" ;;
	g) graph=true;;
        *) help ;;

    esac
done

if $graph; then

    if [[ -f "bubble_c_resultado.csv" && -f "bubble_python_resultado.csv" && \
          -f "merge_c_resultado.csv" && -f "merge_python_resultado.csv" ]]; then

	gnuplot grafico.gnu

        echo "Gráfico salvo em grafico_resultados.png"
        exit 0
    else
        echo "Erro: Um ou mais arquivos CSV necessários não foram encontrados."
        exit 1
    fi
fi



if [[ -z $language || -z $algorithm || -z $num_executions || -z $input_sizes ]]; then
    echo "Erro: Todos os parâmetros -l, -a, -n e -t são obrigatórios."
    help
fi


output_file="${algorithm}_${language}_resultado.csv"





for size in "${input_sizes[@]}"; do
    echo "Executando $algorithm em $language para tamanho de entrada $size..."
    total_time=0

    for ((i = 1; i <= num_executions; i++)); do
        echo "Execução $i para tamanho $size..."

        if [[ $language == "python" ]]; then
            tempo=$(python3 main1.py -a "$algorithm" -n 1 -t "$size")
        elif [[ $language == "c" ]]; then
            if [[ $algorithm == "bubble" ]];then
             tempo=$(./codigo_bubble.out "$size")
             elif [[ $algorithm == "merge" ]]; then
             tempo=$(./codigo_merge.out "$size")
        fi
        else
            echo "Erro: Linguagem não suportada."
            exit 1
        fi

        if [[ ! $tempo =~ ^[0-9]+(\.[0-9]+)?$ ]]; then
            echo "Erro: Tempo de execução inválido para tamanho $size na execução $i."
            exit 1
        fi

        total_time=$(echo "$total_time + $tempo" | bc)
    done

    tempo_medio=$(echo "scale=6; $total_time / $num_executions" | bc)

    # Salva o resultado no arquivo CSV
    echo "$size,$tempo_medio" >> "$output_file"

    echo "Tamanho $size concluído: Tempo médio = $tempo_medio segundos"
done

echo "Resultados salvos em $output_file"
