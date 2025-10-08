[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCA9548A
[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pca9548a/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE) 

Der PCA9548A ist ein oktaler bidirektionaler Umsetzer, der über den I2C-Bus gesteuert wird. Das SCL/SDA-Upstream-Paar fächert sich in acht Downstream-Paare oder Kanäle auf. Jeder einzelne SCx/SDx-Kanal oder jede Kanalkombination kann ausgewählt werden, bestimmt durch den Inhalt des programmierbaren Steuerregisters. Ein aktiver LOW-Reset-Eingang ermöglicht dem PCA9548A die Wiederherstellung aus einer Situation, in der einer der Downstream-I2C-Busse im LOW-Zustand feststeckt. Das Ziehen des RESET-Pins auf LOW setzt die I2C-Bus-Zustandsmaschine zurück und bewirkt die Abwahl aller Kanäle, ebenso wie die interne Power-On-Reset-Funktion. Die Durchgangsgates der Schalter sind so konstruiert, dass der VDD-Pin verwendet werden kann, um die maximal vom PCA9548A durchgelassene Hochspannung zu begrenzen. Dies ermöglicht die Verwendung unterschiedlicher Busspannungen auf jedem Paar, sodass 1,8-V-, 2,5-V- oder 3,3-V-Teile ohne zusätzlichen Schutz mit 5-V-Teilen kommunizieren können. Externe Pull-Up-Widerstände ziehen den Bus für jeden Kanal auf das gewünschte Spannungsniveau. Alle I/O-Pins sind 6 V-tolerant.

LibDriver PCA9548A ist ein vollfunktionaler Treiber für PCA9548A, der von LibDriver veröffentlicht wurde. Er bietet I2C-Kanalumschaltung, I2C-Schreiben, I2C-Lesen und zusätzliche Funktionen. LibDriver ist MISRA-kompatibel.

### Inhaltsverzeichnis

  - [Anweisung](#Anweisung)
  - [Installieren](#Installieren)
  - [Nutzung](#Nutzung)
    - [example basic](#example-basic)
  - [Dokument](#Dokument)
  - [Beitrag](#Beitrag)
  - [Lizenz](#Lizenz)
  - [Kontaktieren Sie uns](#Kontaktieren-Sie-uns)

### Anweisung

/src enthält LibDriver PCA9548A-Quelldateien.

/interface enthält die plattformunabhängige Vorlage LibDriver PCA9548A IIC.

/test enthält den Testcode des LibDriver PCA9548A-Treibers und dieser Code kann die erforderliche Funktion des Chips einfach testen.

/example enthält LibDriver PCA9548A-Beispielcode.

/doc enthält das LibDriver PCA9548A-Offlinedokument.

/Datenblatt enthält PCA9548A-Datenblatt.

/project enthält den allgemeinen Beispielcode für Linux- und MCU-Entwicklungsboards. Alle Projekte verwenden das Shell-Skript, um den Treiber zu debuggen, und die detaillierten Anweisungen finden Sie in der README.md jedes Projekts.

/misra enthält die Ergebnisse des LibDriver MISRA Code Scans.

### Installieren

Verweisen Sie auf eine plattformunabhängige IIC-Schnittstellenvorlage und stellen Sie Ihren Plattform-IIC-Treiber fertig.

Fügen Sie das Verzeichnis /src, den Schnittstellentreiber für Ihre Plattform und Ihre eigenen Treiber zu Ihrem Projekt hinzu. Wenn Sie die Standardbeispieltreiber verwenden möchten, fügen Sie das Verzeichnis /example zu Ihrem Projekt hinzu.

### Nutzung

Sie können auf die Beispiele im Verzeichnis /example zurückgreifen, um Ihren eigenen Treiber zu vervollständigen. Wenn Sie die Standardprogrammierbeispiele verwenden möchten, erfahren Sie hier, wie Sie diese verwenden.

#### example basic

```C
#include "driver_pca9548a_basic.h"

uint8_t res;
uint8_t i;
uint8_t buf[8];
uint8_t data = 0x00;
uint8_t dev_addr = 0x00;
uint16_t reg = 0x0000;
uint16_t len = 1;

/* basic init */
res = pca9548a_basic_init(PCA9548A_ADDRESS_A000);
if (res != 0)
{
    return 1;
}

...
    
/* set channel */
res = pca9548a_basic_set_channel(PCA9548A_CHANNEL_0, PCA9548A_BOOL_TRUE);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}

...
    
/* iic read command */
res = pca9548a_basic_iic_read_command(dev_addr, buf, len);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: data is ");
for (i = 0; i < len; i++)
{
    pca9548a_interface_debug_print("0x%02X ", buf[i]);
}
pca9548a_interface_debug_print("\n");

...

/* iic read */
res = pca9548a_basic_iic_read(dev_addr, reg & 0xFF, buf, len);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: register address 0x%02X.\n", reg);
pca9548a_interface_debug_print("pca9548a: data is ");
for (i = 0; i < len; i++)
{
    pca9548a_interface_debug_print("0x%02X ", buf[i]);
}
pca9548a_interface_debug_print("\n");    

...

/* iic read16 */
res = pca9548a_basic_iic_read_address16(dev_addr, reg, buf, len);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: register address 0x%04X.\n", reg);
pca9548a_interface_debug_print("pca9548a: data is ");
for (i = 0; i < len; i++)
{
    pca9548a_interface_debug_print("0x%02X ", buf[i]);
}
pca9548a_interface_debug_print("\n");  

...

/* iic write command */
res = pca9548a_basic_iic_write_command(dev_addr, &data, 1);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: data is 0x%02X\n", data); 

...

/* iic write */
res = pca9548a_basic_iic_write(dev_addr, reg & 0xFF, &data, 1);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: register address 0x%02X.\n", reg);
pca9548a_interface_debug_print("pca9548a: data is 0x%02X\n", data);    

...

/* iic write */
res = pca9548a_basic_iic_write_address16(dev_addr, reg, &data, 1);
if (res != 0)
{
    (void)pca9548a_basic_deinit();

    return 1;
}
pca9548a_interface_debug_print("pca9548a: device address 0x%02X.\n", dev_addr);
pca9548a_interface_debug_print("pca9548a: register address 0x%04X.\n", reg);
pca9548a_interface_debug_print("pca9548a: data is 0x%02X\n", data);  

...
    
/* basic deinit */
(void)pca9548a_basic_deinit();

return 0;
```

### Dokument

Online-Dokumente: [https://www.libdriver.com/docs/pca9548a/index.html](https://www.libdriver.com/docs/pca9548a/index.html).

Offline-Dokumente: /doc/html/index.html.

### Beitrag

Bitte beachten Sie CONTRIBUTING.md.

### Lizenz

Urheberrechte © (c) 2015 - Gegenwart LibDriver Alle Rechte vorbehalten



Die MIT-Lizenz (MIT)



Hiermit wird jeder Person kostenlos die Erlaubnis erteilt, eine Kopie zu erhalten

dieser Software und zugehörigen Dokumentationsdateien (die „Software“) zu behandeln

in der Software ohne Einschränkung, einschließlich, aber nicht beschränkt auf die Rechte

zu verwenden, zu kopieren, zu modifizieren, zusammenzuführen, zu veröffentlichen, zu verteilen, unterzulizenzieren und/oder zu verkaufen

Kopien der Software und Personen, denen die Software gehört, zu gestatten

dazu eingerichtet werden, unter folgenden Bedingungen:



Der obige Urheberrechtshinweis und dieser Genehmigungshinweis müssen in allen enthalten sein

Kopien oder wesentliche Teile der Software.



DIE SOFTWARE WIRD "WIE BESEHEN" BEREITGESTELLT, OHNE JEGLICHE GEWÄHRLEISTUNG, AUSDRÜCKLICH ODER

STILLSCHWEIGEND, EINSCHLIESSLICH, ABER NICHT BESCHRÄNKT AUF DIE GEWÄHRLEISTUNG DER MARKTGÄNGIGKEIT,

EIGNUNG FÜR EINEN BESTIMMTEN ZWECK UND NICHTVERLETZUNG VON RECHTEN DRITTER. IN KEINEM FALL DARF DAS

AUTOREN ODER URHEBERRECHTSINHABER HAFTEN FÜR JEGLICHE ANSPRÜCHE, SCHÄDEN ODER ANDERE

HAFTUNG, OB AUS VERTRAG, DELIKT ODER ANDERWEITIG, ENTSTEHEND AUS,

AUS ODER IM ZUSAMMENHANG MIT DER SOFTWARE ODER DER VERWENDUNG ODER ANDEREN HANDLUNGEN MIT DER

SOFTWARE.

### Kontaktieren Sie uns

Bitte senden Sie eine E-Mail an lishifenging@outlook.com.