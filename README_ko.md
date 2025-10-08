[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver PCA9548A

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/pca9548a/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

PCA9548A는 I2C 버스를 통해 제어되는 8진 양방향 변환 스위치입니다. SCL/SDA 업스트림 쌍은 8개의 다운스트림 쌍 또는 채널로 확장됩니다. 프로그래밍 가능한 제어 레지스터의 내용에 따라 개별 SCx/SDx 채널 또는 채널 조합을 선택할 수 있습니다. 활성 LOW 리셋 입력을 통해 PCA9548A는 다운스트림 I2C 버스 중 하나가 LOW 상태에 고정된 상황에서 복구할 수 있습니다. RESET 핀을 LOW로 설정하면 I2C 버스 상태 머신이 리셋되고 모든 채널이 선택 해제되며 내부 전원 켜기 리셋 기능도 해제됩니다. 스위치의 패스 게이트는 VDD 핀을 사용하여 PCA9548A에 전달되는 최대 고전압을 제한할 수 있도록 설계되었습니다. 이를 통해 각 쌍에서 서로 다른 버스 전압을 사용할 수 있으므로 1.8V, 2.5V 또는 3.3V 부품이 추가 보호 없이 5V 부품과 통신할 수 있습니다. 외부 풀업 저항은 각 채널에 대해 원하는 전압 레벨까지 버스를 끌어올립니다. 모든 I/O 핀은 6V까지 허용됩니다.

LibDriver PCA9548A는 LibDriver에서 출시한 PCA9548A용 모든 기능을 갖춘 드라이버입니다. I2C 채널 전환, I2C 쓰기, I2C 읽기 및 추가 기능을 제공합니다. LibDriver는 MISRA 표준을 준수합니다.

### 콘텐츠

  - [설명](#설명)
  - [설치](#설치)
  - [사용](#사용)
    - [example basic](#example-basic)
  - [문서](#문서)
  - [기고](#기고)
  - [저작권](#저작권)
  - [문의하기](#문의하기)

### 설명

/src 디렉토리에는 LibDriver PCA9548A의 소스 파일이 포함되어 있습니다.

/interface 디렉토리에는 LibDriver PCA9548A용 플랫폼 독립적인 IIC버스 템플릿이 포함되어 있습니다.

/test 디렉토리에는 LibDriver PCA9548A드라이버 테스트 프로그램이 포함되어 있어 칩의 필요한 기능을 간단히 테스트할 수 있습니다.

/example 디렉토리에는 LibDriver PCA9548A프로그래밍 예제가 포함되어 있습니다.

/doc 디렉토리에는 LibDriver PCA9548A오프라인 문서가 포함되어 있습니다.

/datasheet 디렉토리에는 PCA9548A데이터시트가 있습니다.

/project 디렉토리에는 일반적으로 사용되는 Linux 및 마이크로컨트롤러 개발 보드의 프로젝트 샘플이 포함되어 있습니다. 모든 프로젝트는 디버깅 방법으로 셸 스크립트를 사용하며, 자세한 내용은 각 프로젝트의 README.md를 참조하십시오.

/misra 에는 LibDriver misra 코드 검색 결과가 포함됩니다.

### 설치

/interface 디렉토리에서 플랫폼 독립적인 IIC버스 템플릿을 참조하여 지정된 플랫폼에 대한 IIC버스 드라이버를 완성하십시오.

/src 디렉터리, 플랫폼용 인터페이스 드라이버 및 자체 드라이버를 프로젝트에 추가합니다. 기본 예제 드라이버를 사용하려면 /example 디렉터리를 프로젝트에 추가합니다.

### 사용

/example 디렉터리의 예제를 참조하여 자신만의 드라이버를 완성할 수 있습니다. 기본 프로그래밍 예제를 사용하려는 경우 사용 방법은 다음과 같습니다.

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

### 문서

온라인 문서: [https://www.libdriver.com/docs/pca9548a/index.html](https://www.libdriver.com/docs/pca9548a/index.html).

오프라인 문서: /doc/html/index.html.

### 기고

CONTRIBUTING.md 를 참조하십시오.

### 저작권

저작권 (c) 2015 - 지금 LibDriver 판권 소유

MIT 라이선스(MIT)

이 소프트웨어 및 관련 문서 파일("소프트웨어")의 사본을 얻은 모든 사람은 이에 따라 무제한 사용, 복제, 수정, 통합, 출판, 배포, 2차 라이선스를 포함하여 소프트웨어를 처분할 수 있는 권리가 부여됩니다. 소프트웨어의 사본에 대한 라이선스 및/또는 판매, 그리고 소프트웨어가 위와 같이 배포된 사람의 권리에 대한 2차 라이선스는 다음 조건에 따릅니다.

위의 저작권 표시 및 이 허가 표시는 이 소프트웨어의 모든 사본 또는 내용에 포함됩니다.

이 소프트웨어는 상품성, 특정 목적에의 적합성 및 비침해에 대한 보증을 포함하되 이에 국한되지 않는 어떠한 종류의 명시적 또는 묵시적 보증 없이 "있는 그대로" 제공됩니다. 어떤 경우에도 저자 또는 저작권 소유자는 계약, 불법 행위 또는 기타 방식에 관계없이 소프트웨어 및 기타 소프트웨어 사용으로 인해 발생하거나 이와 관련하여 발생하는 청구, 손해 또는 기타 책임에 대해 책임을 지지 않습니다.

### 문의하기

연락주세요lishifenging@outlook.com.