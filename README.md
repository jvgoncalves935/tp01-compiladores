# tp01-compiladores

Descrição: Um analisador léxico de códigos de C que gera uma lista de todos os tokens de um código .C. Projeto implementado em C.
Projeto foi testado apenas no Bash do Ubuntu para Windows 10. Outras plataformas como distribuições nativas de Linux ou Windows podem gerar comportamentos desconhecidos.

Instruções:
  -Compilar: Comando "make" em algum terminal, na pasta raiz do projeto.
  -Executar: ./tp1 -a (diretorio_do_arquivo)
  -Exemplo: ./tp1 -a files/teste01.c
  -Resultados:
    .Se houverem erros léxicos: Serão exibidas as linhas e colunas de onde ocorreram caracteres não reconhecidos pelo analisador. Sem saída em arquivos.
    .Se não houverem erros léxicos: Lista de tokens e listas de categorias de tokens serão criadas na pasta "out".
    .Exemplo de saída (arquivo /files/teste01.c):
      ./out/teste01_tabela.txt (Lista de Tokens, todos os tokens)
      ./out/teste01_identificadores.txt (Lista de Identificadores)
      ./out/teste01_reservadas.txt (Lista de Palavras Reservadas)
      ./out/teste01_comentarios.txt (Lista de Comentários)
      ./out/teste01_diretiva.txt (Lista de Diretivas)
      ./out/teste01_literais.txt (Lista de Literais)
      ./out/teste01_numeros.txt (Lista de Números)
      ./out/teste01_operadores.txt (Lista de Operadores)
      ./out/teste01_separadores (Lista de Separadores)
