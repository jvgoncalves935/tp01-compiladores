# tp01-compiladores

Descrição:

Um analisador léxico de códigos de C que gera uma lista de todos os tokens de um código .C. Projeto implementado em C.
Projeto foi testado apenas no Bash do Ubuntu para Windows 10. Outras plataformas como distribuições nativas de Linux ou Windows podem gerar comportamentos desconhecidos.

Instruções:

- Compilar: Comando "make" em algum terminal, na pasta raiz do projeto.
  
- Executar: ./tp1 -a (diretorio_do_arquivo)
  
- Exemplo: ./tp1 -a files/teste01.c
  
- Resultados:
    - Se houverem erros léxicos: Serão exibidas as linhas e colunas de onde ocorreram caracteres não reconhecidos pelo analisador. Sem saída em arquivos.
    - Se não houverem erros léxicos: Lista de tokens e listas de categorias de tokens serão criadas na pasta "out".
    
- Exemplo de saída (arquivo /files/teste01.c):
  - /out/teste01_tabela.txt (Lista de Tokens, todos os tokens)
  - /out/teste01_identificadores.txt (Lista de Identificadores)
  - /out/teste01_reservadas.txt (Lista de Palavras Reservadas)
  - /out/teste01_comentarios.txt (Lista de Comentários)
  - /out/teste01_diretiva.txt (Lista de Diretivas)
  - /out/teste01_literais.txt (Lista de Literais)
  - /out/teste01_numeros.txt (Lista de Números)
  - /out/teste01_operadores.txt (Lista de Operadores)
  - /out/teste01_separadores (Lista de Separadores)
 
 # Tabela de Tokens
 
| Token                | Classe        | Conjunto                                                                 |
|----------------------|---------------|--------------------------------------------------------------------------|
| identificador        | Identificador | abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ                     |
| numero               | Numero        | 0123456789,'.'                                                           |
| diretiva             | Diretiva      | Linha que inicia com '#'                                                 |
| comentario           | Comentario    | Linha que inicia com "//" ou conjunto com qualquer caracter entre "/**/" |
| aspas_simples        | Literal       | Caracter entre ''                                                        |
| aspas_duplas         | Literal       | Conjunto com qualquer caracter entre ""                                  |
| espaco               | Separador     | ' '                                                                      |
| ponto_virgula        | Separador     | ';'                                                                      |
| quebra_linha         | Separador     | '\n'                                                                     |
| retorno_de_carruagem | Separador     | '\r'                                                                     |
| tabulacao            | Separador     | '\t'                                                                     |
| abre_parenteses      | Separador     | '('                                                                      |
| fecha_parenteses     | Separador     | ')'                                                                      |
| abre_colchetes       | Separador     | '['                                                                      |
| fecha_colchetes      | Separador     | ']'                                                                      |
| abre_chaves          | Separador     | '{'                                                                      |
| fecha_chaves         | Separador     | '}'                                                                      |
| ponto                | Separador     | '.'                                                                      |
| virgula              | Separador     | ','                                                                      |
| dois_pontos          | Separador     | ':'                                                                      |
| mais	               | Operador      | '+'                                                                      |
| vezes	               | Operador      | '*'                                                                      |
| porcento             | Operador      | '%'                                                                      |
| barra	               | Operador      | '/'                                                                      |
| igual	               | Operador      | '='                                                                      |
| menor	               | Operador      | '<'                                                                      |
| maior	               | Operador      | '>'                                                                      |
| negacao              | Operador      | '!'                                                                      |
| or_simples           | Operador      | '(pipeline)'															  |
| and_simples          | Operador      | '&'                                                                      |
| til	               | Operador      | '~'                                                                      |
| circunflexo          | Operador      | '^'                                                                      |
| menos	               | Operador      | '-'                                                                      |
| interrogacao         | Operador      | '?'													         		  |
| mais_igual	       | Operador      | '+='													         		  |
| mais_mais		       | Operador      | '++'													         		  |
| menos_igual          | Operador      | '-='													         		  |
| menos_menos          | Operador      | '--'													         		  |
| vezes_igual          | Operador      | '*='													         		  |
| vezes_vezes	       | Operador      | '**'													         		  |
| barra_igual          | Operador      | '/='													         		  |
| igual_igual          | Operador      | '=='													         		  |
| diferente	           | Operador      | '!='													         		  |
| menor_igual	       | Operador      | '<='													         		  |
| maior_igual          | Operador      | '>='													         		  |
| or_duplo             | Operador      | '(pipeline)(pipeline)'									         		  |
| and_igual            | Operador      | '&&'													         		  |
| (nome da palavra)    | Reservada     | (conjunto de palavras reservadas)                                        |

# Lista de Palavras Reservadas

|          |          |          |        |
|----------|----------|----------|--------|
| auto     | break    | case     | char   |
| const    | continue | default  | do     |
| int      | long     | register | return |
| short    | signed   | sizeof   | static |
| struct   | switch   | typedef  | union  |
| unsigned | void     | volatile | while  |
| double   | else     | enum     | extern |
| float    | for      | goto     | if     |
