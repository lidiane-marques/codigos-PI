import time
import random
import argparse

def bubble_sort(arr):
    n = len(arr)
    for i in range(n):
        for j in range(0, n-i-1):
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

def merge_sort(arr):
    if len(arr) > 1:
        mid = len(arr) // 2
        left_half = arr[:mid]
        right_half = arr[mid:]

        merge_sort(left_half)
        merge_sort(right_half)

        i = j = k = 0
        while i < len(left_half) and j < len(right_half):
            if left_half[i] < right_half[j]:
                arr[k] = left_half[i]
                i += 1
            else:
                arr[k] = right_half[j]
                j += 1
            k += 1

        while i < len(left_half):
            arr[k] = left_half[i]
            i += 1
            k += 1
        while j < len(right_half):
            arr[k] = right_half[j]
            j += 1
            k += 1

    return arr

def run_sorting_algorithm(algorithm, size):
    arr = [random.randint(0, 10000) for _ in range(size)]
    start_time = time.time()

    if algorithm == 'bubble':
        bubble_sort(arr)
    elif algorithm == 'merge':
        merge_sort(arr)

    end_time = time.time()
    return end_time - start_time

def run_multiple_executions(algorithm, size, num_executions):
    total_time = 0
    for _ in range(num_executions):
        total_time += run_sorting_algorithm(algorithm, size)
    return total_time / num_executions

 
parser = argparse.ArgumentParser(description="Executa algoritmos de ordenação e gera log em CSV.")
parser.add_argument('-a', '--algorithm', type=str, required=True, choices=['bubble', 'merge'], help="Algoritmo a ser executado (bubble ou merge)")
parser.add_argument('-t', '--input_size', type=str, required=True, help="Tamanho da entrada para o algoritmo")
parser.add_argument('-n', '--num_executions', type=int, required=True, help="Número de vezes que o algoritmo será executado")
args = parser.parse_args()


input_sizes = [int(size.strip()) for size in args.input_size.split(',')]

for size in input_sizes:
    average_time = run_multiple_executions(args.algorithm, size, args.num_executions)
    print(f"{average_time:.6f}")
