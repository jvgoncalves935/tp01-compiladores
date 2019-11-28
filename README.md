# Compilador-C (código sujeito a mudanças)

Descrição:

Compilador de C implementado em C. NÃO abrange a gramática completa do C e foi desenvolvido apenas por fins de aprendizado.

Analisador léxico: gera uma lista de todos os tokens de um código .C.
Analisador sintático: monta uma árvore sintática à partir da lista de tokens. A árvore é montada à partir de funções recursivas, utilizando a própria pilha do SO.
Analisador semântico: analisa erros semânticos durante a análise sintática.
Gerador de código assembly: (WIP).

Projeto foi testado apenas no Bash do Ubuntu para Windows 10. Outras plataformas como distribuições nativas de Linux ou Windows podem gerar undefined behaviors.

Instruções:

- Compilar: Comando "make" em algum terminal, na pasta raiz do projeto.
  
- Flags de execução:
	-a: Nome do arquivo. (Flag obrigatória)
	-s: Ativar exibição da Árvore Sintática. (Opcional)
- Executar: ./tp1 -a (diretorio_do_arquivo)		(Árvore sintática omitida)
			./tp1 -a (diretorio_do_arquivo) -s  (Árvore sintática visível)
- Exemplo: ./tp1 -a files/teste01.c -s
  
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
 
 # Analisador Léxico
 
 ### Tabela de Tokens
 
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

### Lista de Palavras Reservadas

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

# Analisador Sintático

### Gramática Livre de Contexto - "JVGLC"

- (listaDiretivas) ::= diretiva (listaDiretivas) |
- (listaDiretivas) ::= ε
<br/>

- (linguagem) ::= (funcao) /*enquanto lista de tokens não estiver vazia*/
<br/>

- (funcao) ::= (tipo) identificador abre_parenteses (listaArg) fecha_parenteses (statementEscopo)
<br/>

- (tipo) ::= int |
- (tipo) ::= float |
- (tipo) ::= char |
- (tipo) ::= double |
- (tipo) ::= void
<br/>

- (listaArg) ::= (arg) |
- (listaArg) ::= virgula (listaArg) |
- (listaArg) ::= ε
<br/>

- (arg) ::= (tipo) identificador |
<br/>

- (declaracao) ::= (tipo) (listaIdentificadores) |
- (declaracao) ::= ε
<br/>

- (listaIdentificadores) ::= identificador |
- (listaIdentificadores) ::= identificador virgula (listaIdentificadores)
<br/>

- (statement) ::= (statementFor) |
- (statement) ::= (statementWhile) |
- (statement) ::= (expressao) ponto_virgula |
- (statement) ::= (statementIf) |
- (statement) ::= (statementEscopo) |
- (statement) ::= (declaracao) |
- (statement) ::= (statementDoWhile) |
- (statement) ::= return (statementReturn) ponto_virgula |
- (statement) ::= break ponto_virgula |
- (statement) ::= (switch01) |
- (statement) ::= ponto_virgula
<br/>

- (statementIf) ::= if abre_parenteses (expressao) fecha_parenteses (statement) (parteElse)
<br/>

- (statementFor) ::= for abre_parenteses (expressao) ponto_virgula (expressaoOpcional) ponto_virgula (expressaoOpcional) fecha_parenteses (statement)
<br/>

- (expressaoOpcional) ::= (expressao) |
- (expressaoOpcional) ::= ε
<br/>

- (statementWhile) ::= while abre_parenteses (expressao) fecha_parenteses (statement)
<br/>

- (statementDoWhile) ::= do (statementEscopo) while abre_parenteses (expressao) fecha_parenteses
<br/>

- (parteElse) ::= else (statement) |
- (parteElse) ::= ε
<br/>

- (statementReturn) := identificador |
- (statementReturn) := numero |
- (statementReturn) := literal_simples |
- (statementReturn) := literal_duplo |
- (statementReturn) := ε
<br/>

- (statementEscopo) ::= abre_chaves (listaStatement) fecha_chaves
<br/>

- (listaStatement) ::= (statement) (listaStatementLinha)
<br/>

- (listaStatementLinha) ::= (statement) (listaStatementLinha) |
- (listaStatementLinha) ::= ε
<br/>

- (expressao) ::= identificador (expressao02) |
- (expressao) ::= (valorR)
<br/>

- (expressao02) ::= igual (expressao) |
- (expressao02) ::= (comparacao) (expressao) |
- (expressao02) ::= (aritmetica) (expressao) |
- (expressao02) ::= (aritmeticaOperadorDuplicado) |
- (expressao02) ::= (aritmeticaOperadorIgualComposto) (expressao)
<br/>

- (valorR) ::= (comparacao) (magnitude) (valorRLinha) |
- (valorR) ::= (magnitude)
<br/>

- (valorRLinha) ::= (comparacao) (magnitude) (valorRLinha) |
- (valorRLinha) ::= ε
<br/>

- (comparacao) ::= igual_igual|
- (comparacao) ::= menor |
- (comparacao) ::= maior |
- (comparacao) ::= menor_igual |
- (comparacao) ::= maior_igual |
- (comparacao) ::= diferente
<br/>

- (magnitude) ::= (termo) (magnitudeLinha)
<br/>

- (termo) ::= (fator) (termoLinha)
<br/>

- (magnitudeLinha) ::= mais (termo) (magnitudeLinha) |
- (magnitudeLinha) ::= menos (termo) (magnitudeLinha) |
- (magnitudeLinha) ::= ε
<br/>

- (termoLinha) ::= vezes (fator) (termoLinha) |
- (termoLinha) ::= barra (fator) (termoLinha) |
- (termoLinha) ::= ε
<br/>

- (fator) ::= abre_parenteses (expressao) fecha_parenteses |
- (fator) ::= menos (fator) |
- (fator) ::= mais (fator) |
- (fator) ::= identificador |
- (fator) ::= numero |
- (fator) ::= aspas_simples |
- (fator) ::= aspas_duplas
<br/>

- (aritmetica) := mais |
- (aritmetica) := menos |
- (aritmetica) := vezes |
- (aritmetica) := barra
<br/>

- (aritmeticaOperadorDuplicado) ::= mais_mais |
- (aritmeticaOperadorDuplicado) ::= menos_menos |
- (aritmeticaOperadorDuplicado) ::= vezes_vezes
<br/>

- (aritmeticaOperadorIgualComposto)	::= mais_igual |
- (aritmeticaOperadorIgualComposto)	::= menos_igual |
- (aritmeticaOperadorIgualComposto)	::= vezes_igual |
- (aritmeticaOperadorIgualComposto)	::= barra_igual
<br/>

- (switch01) ::= switch abre_parenteses	(switch02) fecha_parenteses abre_chaves (listaCase) fecha_chaves
<br/>

- (switch02) ::= numero
- (switch02) ::= identificador
- (switch02) ::= aspas_simples
- (switch02) ::= aspas_duplas 
<br/>

- (listaCase) ::= case (switch02) dois_pontos (listaStatement) (listaCaseLinha)
<br/>

- (listaCaseLinha) ::= case (switch02) dois_pontos (listaStatement) (listaCaseLinha) |
- (listaCaseLinha) ::= default dois_pontos (listaStatement) |
- (listaCaseLinha) ::= ε
<br/>

- (chamadaFuncao) ::= identificador abre_parenteses (listaArgChamadaFuncao) fecha_parenteses ponto_virgula
<br/>

- (listaArgChamadaFuncao) ::= (switch02) (listaArgChamadaFuncaoLinha) |
- (listaArgChamadaFuncao) ::= ε
<br/>

- (listaArgChamadaFuncaoLinha) ::= virgula (switch02) (listaArgChamadaFuncaoLinha) |
- (listaArgChamadaFuncaoLinha) ::= ε
<br/>

# Analisador Semântico

### Erros Semânticos
- Variáveis não declaradas.
- Operações com tipos de variáveis distintas (não existe operações de alargamento e estreitamento).
- Atribuições em variáveis não declaradas.

### Warnings Semânticos
- Variáveis declaradas porém não inicializadas.
