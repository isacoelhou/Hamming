import sys
from math import *

def aloc_C(array_dados, testes):
    array_dados.insert(0, "G")
    for i in range(testes):
        indice = ceil(pow(2, i))
        array_dados.insert(indice, "C") #add o bit G no lugar fixo dele e aloca os C em seus devidos lugares

def Write_arq_W(array_txt):
    chave_arq = open("string_chave.txt", 'w')
    chave_arq.write(array_txt)
    print("Código hamming efetuado com sucesso! Criando arquivo .wham")
    print("Documento .wham foi criado com sucesso!")
    chave_arq.close()

def Write_arq_C(file_name, array):
    corrupted_arq = open(file_name, "w+")
    corrupted_arq.write(array)
    print("Seu erro foi corrigido com sucesso!")
    corrupted_arq.close()

def choice_W(file_name):        
    #abertura de aruqivo e leitura
    auxfile = open(file_name, "rb")
    file_array = auxfile.read()
    #////////////////////////////////////////
    #definicao de variaveis
    string_dados = ""
    aux_xor = 0
    quant_um = []
    aux_array = list()
    counter = 0
    array_txt = list()
    array_chave = " "
    #////////////////////////////////////////
    for i in file_array:
        byte = bin(i)[2:].rjust(8, '0')
        string_dados += byte            #tranforma em binario e passa valor 0 caso seja menor q euqivalente a 1 byte
   
    strdados = string_dados[::-1]
    c_test = floor(log2(len(string_dados)))+1 #inverte a string e adiciona a quantidade de bits testes C + 1 que e o G 

    list_strdados = list(strdados)

    aloc_C(list_strdados, c_test)

    enumerate(list_strdados)

    for i in range(len(list_strdados)): #lista todos os elementos 1 para posteriomente fazer a xor dele
        if(list_strdados[i] == '1'):
            quant_um.append(i)
    
    for i in range(len(quant_um)):
        aux_xor = aux_xor ^ quant_um[i] #realiza a xor retorna um inteiro com o valor de C 

    Xor = bin(aux_xor)[2:].rjust(8, '0')
    list_Xor = list(Xor)    #tranforma o numero anterior em binario, entao inverte para ficar o numero normal
    list_Xor.reverse()

    for i in range(len(list_Xor)):
        if(list_Xor[i] == '1'):
            if(i == 0): 
                aux_array.append(1)     #Essa funcao é usada no proximo for para comparar os bits de testes e atribuilos como 1 ou 0
            else:
                aux_array.append(i+1)
    
    for i in range(len(list_strdados)):
        if(list_strdados[i] == 'C'):
            counter += 1
            for j in range(len(aux_array)): #Faz o calculo do C de e adiciona seus respectivos valores 
                if(aux_array[j] == counter):
                    list_strdados[i] = 1
            if(list_strdados[i] == 'C'):
                list_strdados[i] = 0
    
    counter = 0

    for i  in range(len(list_strdados)):
        array_txt.append(str(list_strdados[i])) #adiciona a lista de dados tranformando ela em string para array_txt

    for i in range(len(array_txt)):
        if(array_txt[i] == '1'):    #conta todos os 1, no mesmo estilo acima usado 
            counter += 1
    
    if(counter%2 == 0):
        array_txt[0] = '0'
    else:                       #pega o counter e verifica o bit G, ou seja, verifica se é par ou não 
        array_txt[0] = '1'
    
    for i in range(len(array_txt)):
        array_chave = array_chave + array_txt[i]    #junta a string resultante em um outro array para poder gravar no arquivo, pq se nao da erro

    Write_arq_W(array_chave)
    auxfile.close()

def choice_C(file_name):
    #le string e passa para uma lista
    auxfile = open(file_name, "r+")
    array_code = auxfile.read()
    code_string = array_code.rsplit()[0]
    e_par = bool
    #declaracao de variaveis
    list_code = list(code_string)
    quant_um = []
    index_notG = 1
    counter = 0
    aux_xor = 0
    right_code = ""

    auxfile.close()

    for index_notG in range(len(list_code)): #armazena os indices para posteriormente fazer um xor
        if(list_code[index_notG] == '1'):
            quant_um.append(index_notG)

    for i in range(len(list_code)): #conta os 1
        if(list_code[i] == '1'):
            counter+=1
    
    if(counter%2==0): #descobre se o numero eh par ou nao
        e_par = True
    else:
        e_par = False
    
    for i in range(len(quant_um)):
        aux_xor = aux_xor ^ quant_um[i] #aplica o xor

    if(aux_xor != 0 and e_par == False):
        print("Falha detectada! Preparando para a correção")

        if(list_code[aux_xor] == '0'):
            list_code[aux_xor] = '1' #corrige o bit errado
        else:
            list_code[aux_xor] = '0'

        for i in range(len(list_code)): #encontra onde posicionar o bit corrigido
            right_code = right_code + list_code[i] 
            
        Write_arq_C(file_name, right_code)#ajustar o write-arq

    elif(aux_xor!=0 and e_par == True):
        print("Falha detectada! Preparando para a correção")
        print("Falha não pode ser corrigida")     

    elif(aux_xor == 0 and e_par == False): #mesmo de cima
        print("Falha detectada! Preparando para a correção")
        if(list_code[0] == '0'):
            list_code[0] = '1'
        else:
            list_code[0] = '0'

        for i in range(len(list_code)):
            right_code = right_code + list_code[i]
        
        Write_arq_C(file_name, right_code)

    elif(aux_xor == 0 and e_par == True):
        print("Nenhuma falha detectada! Seu arquivo não está corrompido")


code_or_decode = sys.argv[2] 
file_name = sys.argv[1]

if(code_or_decode == 'w'):
    choice_W(file_name)

elif(code_or_decode == 'c'):
   choice_C(file_name)
