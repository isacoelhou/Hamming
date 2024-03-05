Elaborar um simulador de armazenamento seguro (utilizando SEC-DED) de arquivos binários:
Funcionamento para gravação:
a- O arquivo para armazenamento deve ser passado via parâmetro no prompt/terminal
    a1- ou ser possível de selecionar nos simuladores com interface gráfica
b- Deve ser mostrado os principais passos para produção da palavra síndrome + bit G (M = 8)
c- Deve ser salvo um novo arquivo com SEC-DED no formato da tabela 4
Exemplo:
$ ./hamming arquivoTeste.qqcoisa -w
-w para salvar o arquivo com integridade hamming
Sugestão de extensão para o arquivo com integridade: arquivoTeste.qqcoisa.wham
Funcionamento para leitura:
d- O arquivo para leitura deve ser passado via parâmetro no prompt/terminal
    d1- ou ser possível de selecionar nos simuladores com interface gráfica
e- Deve ser mostrado os principais passos para verificação de integridade do arquivo
f- Em caso de falha, executar os procedimentos necessários para correção
    f.1- Salvar o arquivo corrigido
g- Finalizar
Exemplo:
$ ./hamming arquivoTeste.qqcoisa.wham -r
-r para ler o arquivo com integridade hamming, verificar e recuperar (se necessário)