
##Detector de luminosidade - Nexus Group
<p>Turma: 1ESPG</p>

**Integrantes**
|Nome|RM|
|--|--|
|Lucas de Almeida Pires | RM: 562757 |
|Daniel Oliveira de Souza | RM: 566284 |
|João Pedro Raimundo Marcilio | RM: 561603 |
|Lucas Zanella Clemente | RM: 563880 |
|João Pedro Ribeiro Palermo | RM: 562077 |

<p>O Nexus Group desenvolveu um detector de luminosidade feito especialmente para vinhos, capaz de manter informado os usuários que adquiriram o dispositivo sobre a porcentagem de luminosidade que é presente no local, mostrando quando o ambiente se encontra em condições fora do ideal, permitindo uma ação necessária para preservar os produtos.</p>

<h2>Manual</h2>

**Como utilizar:**
<ol>
	<li>Inicie o Arduino.</li>
	<li>No display, ao aparecer "LIGHT ON > THEN PRESS BUTTON", ligue a luz do local.</li>
	<li>Quando a luz do local estiver acessa, pressione o botão por 1 segundo para definir o limite de tolerância do dispositivo.</li>
	<li>Apague a luz do local.</li>
</ol>

<br>

**Como funciona:**
<p>A detecção da luminosidade é feita a partir do fotorresistor que se encontra "plugado" na breadboard, mandando sinais analógicos de acordo com a resistência que ele gera por conta da luz do ambiente, que definimos na configuração inicial do dispositivo. Depois de definido a luz do ambiente, ele toma como base esses valores e gera três tipos de alerta para os usuários no local, esses alertas são ativados nas seguintes condições:
<ul>
	<li>Caso exista ausência de luz ou luz fraquíssima, será acionado a luz verde. 
</li>
	<li>Na existência de uma penumbra com/ou pouca luz, será acionado a luz amarela.</li>
	<li>Durante a existência de luz alta ou total do ambiente, será acionado a luz vermelha e também um dispositivo sonoro que indica a irregularidade do local a cada poucos segundos, se repetindo se a situação se manter.</li>
</ul>
</p>

<br>

<a href="https://www.tinkercad.com/things/iyVf2ghUNdK-checkpoint-1-luminosidade-v3?sharecode=ropxFYCk9jbk4PjHbZS1v8b2ajrwrSzUlY7NPBjDDdA">Aperte aqui para ir até a simulação do Tinkercad!</a>
<br>
<a href="https://www.youtube.com/watch?v=QuvtC4mlm0Q">Aperte aqui para ir até o vídeo explicativo do projeto!</a>

<h2>Componentes e Circuitos</h2>

***Componentes usados:***

| Nome | Quantidade |
|--|--|
|Arduino Uno|1|
|Fotorresistor|1|
|Vermelho LED|1|
|Amarelo LED|1|
|Verde LED|1|
|Piezo (ou Buzzer)|1|
|LCD 16x2|1|
|300 ohms Resistor|4|
|10k ohms Resistor|2|
|100 ohms Resistor|1|
|Botão|1|
|Jumpers| Diversos|


***Esquema elétrico:***
![Esquema elétrico do projeto de luminosidade](https://github.com/Nexus-Consulting-FIAP/Checkpoint1EdgeComputing/blob/main/EsquemaEl%C3%A9tricoLuminosidade.jpg?raw=true)
