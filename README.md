# C_Posix_Basic_Examples

## 1. Makefile

Para os exemplos basta usar o comando `make` para compilar.
O compilador utilizado é o `gcc`, basta tê-lo instalado na máquina.

## 2. Exemplos

### Sincronizacao

Este é um exemplo de implementação de um problema clássico de sincronização chamado "Produtor-Consumidor" usando semáforos em C com POSIX threads. Neste cenário, há um buffer compartilhado entre uma thread produtora e uma thread consumidora. A thread produtora insere itens no buffer, enquanto a thread consumidora retira itens do buffer. A sincronização é realizada usando semáforos para garantir que o produtor e o consumidor não acessem o buffer ao mesmo tempo. O buffer compartilhado é tambem um exemplo de implementação de uma possivel forma de trocar mensagens entre threads. Outro exemplo de possível forma seria por meio de variaveis atomicas, mas isso não é abordado neste exemplo.

#### Funcionamento

1. O buffer é definido com um tamanho fixo (`BUFFER_SIZE``).
2. Duas threads são criadas: uma thread produtora e uma thread consumidora.
3. A thread produtora gera números aleatórios (`item`) e os insere no buffer. Ela aguarda o semáforo `empty` (que representa espaços vazios no buffer) antes de inserir um item.
4. A thread consumidora retira itens do buffer e os imprime. Ela aguarda o semáforo `full` (que representa itens no buffer) antes de retirar um item.
5. O programa cria as threads produtora e consumidora usando a função `pthread_create` e espera que elas terminem usando a função `pthread_join`.
6. Os semáforos empty e full são inicializados com os valores apropriados (BUFFER_SIZE e 0, respectivamente) usando `sem_init`.
7. Após a conclusão das threads, os semáforos são destruídos usando `sem_destroy`.

### Race

Este programa cria duas threads (`tid1` e `tid2`) que executam a função `Count`. A função `Count` realiza um loop onde uma variável tmp é atualizada com o valor atual de `cnt`, depois incrementa tmp e finalmente atualiza `cnt` com o valor de `tmp`.

Como não há sincronização adequada entre as threads para acessar e modificar a variável `cnt`, uma condição de corrida ocorre. Isso significa que as threads podem interferir umas nas outras, causando resultados inconsistentes.

Se a condição de corrida não ocorrer, o valor de `cnt` será igual a `2 * NITER` (o dobro do número de iterações). No entanto, devido à falta de sincronização, é provável que ocorram resultados incorretos, e verá mensagens de erro ou sucesso baseadas na verificação do valor de `cnt`.

**Nota:** Este código é projetado para demonstrar um problema de condição de corrida

### Interrupcao

Este código demonstra como usar interrupções temporais (sinais `SIGALRM`) em C POSIX para agendar a execução de uma ação após um intervalo de tempo específico. Vamos dividir o código em partes para uma melhor compreensão.

1. A função principal começa definindo uma estrutura `struct sigaction` chamada `sa`. Nesta estrutura, o campo `sa_handler` é configurado para a função de tratamento `alarm_handler`, que será chamada quando o temporizador expirar. Os outros campos da estrutura são configurados para valores padrão.
2. A função `sigaction` é usada para configurar o tratador de sinal. Se houver um erro, a função perror exibirá uma mensagem de erro.
3. A função `alarm` é usada para definir um temporizador para 5 segundos. Quando esse tempo expirar, o sinal `SIGALRM` será gerado, o tratador `alarm_handler` será chamado e a mensagem será impressa.
4. O loop `while(1)` faz com que o programa aguarde indefinidamente até que o sinal `SIGALRM` seja recebido. Nesse ponto, a função `alarm_handler` é chamada, o que resulta na impressão da mensagem e no encerramento do programa.

`Nota:` Este exemplo demonstra o uso de interrupções temporais usando sinais `SIGALRM`. No entanto, tenha em mente que o uso de `while(1)` para aguardar sinais pode não ser a melhor abordagem em cenários reais, pois resultaria em alto consumo de CPU. 