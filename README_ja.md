[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCA9548A

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pca9548a/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCA9548Aは、I2Cバスを介して制御される8ビット双方向変換スイッチです。SCL/SDAアップストリームペアは、8つのダウンストリームペア（チャネル）に展開されます。プログラマブル制御レジスタの内容に応じて、任意のSCx/SDxチャネルまたはチャネルの組み合わせを選択できます。アクティブLOWリセット入力により、PCA9548Aは、ダウンストリームI2Cバスの1つがLOW状態でスタックしている状況から回復できます。RESETピンをLOWにすると、I2Cバスステートマシンがリセットされ、内部のパワーオンリセット機能と同様に、すべてのチャネルが選択解除されます。スイッチのパスゲートは、VDDピンを使用してPCA9548Aが通過する最大高電圧を制限できるように設計されています。これにより、各ペアで異なるバス電圧を使用できるため、1.8V、2.5V、または3.3Vのデバイスを、追加の保護なしで5Vのデバイスと通信できます。外付けプルアップ抵抗により、各チャネルのバスを所定の電圧レベルまでプルアップできます。すべてのI/Oピンは6Vトレラントです。

LibDriver PCA9548Aは、LibDriverがリリースしたPCA9548A用のフル機能ドライバです。I2Cチャネル切り替え、I2C書き込み、I2C読み取りなどの追加機能を提供します。LibDriverはMISRAに準拠しています。

### 目次

  - [説明](#説明)
  - [インストール](#インストール)
  - [使用](#使用)
    - [example basic](#example-basic)
  - [ドキュメント](#ドキュメント)
  - [貢献](#貢献)
  - [著作権](#著作権)
  - [連絡して](#連絡して)

### 説明

/ srcディレクトリには、LibDriver PCA9548Aのソースファイルが含まれています。

/ interfaceディレクトリには、LibDriver PCA9548A用のプラットフォームに依存しないIICバステンプレートが含まれています。

/ testディレクトリには、チップの必要な機能を簡単にテストできるLibDriver PCA9548Aドライバーテストプログラムが含まれています。

/ exampleディレクトリには、LibDriver PCA9548Aプログラミング例が含まれています。

/ docディレクトリには、LibDriver PCA9548Aオフラインドキュメントが含まれています。

/ datasheetディレクトリには、PCA9548Aデータシートが含まれています。

/ projectディレクトリには、一般的に使用されるLinuxおよびマイクロコントローラー開発ボードのプロジェクトサンプルが含まれています。 すべてのプロジェクトは、デバッグ方法としてシェルスクリプトを使用しています。詳細については、各プロジェクトのREADME.mdを参照してください。

/ misraはLibDriver misraコードスキャン結果を含む。

### インストール

/ interfaceディレクトリにあるプラットフォームに依存しないIICバステンプレートを参照して、指定したプラットフォームのIICバスドライバを完成させます。

/src ディレクトリ、プラットフォームのインターフェイス ドライバー、および独自のドライバーをプロジェクトに追加します。デフォルトのサンプル ドライバーを使用する場合は、/example ディレクトリをプロジェクトに追加します。

### 使用

/example ディレクトリ内のサンプルを参照して、独自のドライバーを完成させることができます。 デフォルトのプログラミング例を使用したい場合の使用方法は次のとおりです。

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

### ドキュメント

オンラインドキュメント: [https://www.libdriver.com/docs/pca9548a/index.html](https://www.libdriver.com/docs/pca9548a/index.html)。

オフラインドキュメント: /doc/html/index.html。

### 貢献

CONTRIBUTING.mdを参照してください。

### 著作権

著作権（c）2015-今 LibDriver 全著作権所有

MITライセンス（MIT）

このソフトウェアおよび関連するドキュメントファイル（「ソフトウェア」）のコピーを取得した人は、無制限の使用、複製、変更、組み込み、公開、配布、サブライセンスを含む、ソフトウェアを処分する権利を制限なく付与されます。ソフトウェアのライセンスおよび/またはコピーの販売、および上記のようにソフトウェアが配布された人の権利のサブライセンスは、次の条件に従うものとします。

上記の著作権表示およびこの許可通知は、このソフトウェアのすべてのコピーまたは実体に含まれるものとします。

このソフトウェアは「現状有姿」で提供され、商品性、特定目的への適合性、および非侵害の保証を含むがこれらに限定されない、明示または黙示を問わず、いかなる種類の保証もありません。 いかなる場合も、作者または著作権所有者は、契約、不法行為、またはその他の方法で、本ソフトウェアおよび本ソフトウェアの使用またはその他の廃棄に起因または関連して、請求、損害、またはその他の責任を負わないものとします。

### 連絡して

お問い合わせくださいlishifenging@outlook.com。