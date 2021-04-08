### BLC-200

BLC 계열의 모터 드라이버를 연동하는 예제입니다. 자세한 내용은 **예제** 파일 및 **Protocol_BLC_Series.pdf**를 참고하시기 바랍니다.

### 쉴드 연결
BLC 모터 드라이버와 MAS-001 쉴드는 다음과 같이 연결됩니다. (***통신의 안정성을 위해 D+ 와 D-는 Twisted Pair로 연결하시기 바랍니다.***)

| BLC Driver | DMC Driver | MAS-001 |
|:-----------:|:-----------:|:----------------------:|
| D+ | D+ | D+ |
| D- | D- | D- |
| GND | GND | GND |

### 예제

| Example | Description  |
|-----------|----------------------|
| [**BLC-200_DeviceScanning**](./BLC-200_DeviceScanning) | 현재 RS485로 연결된 BLC 드라이버들을 스캔하는 예제입니다. |
| [**BLC-200_DeviceSetting**](./BLC-200_DeviceSetting) | BLC 드라이버의 내부 변수를 세팅하는 예제입니다. |
| [**BLC-200_GetSystemVariables**](./BLC-200_GetSystemVariables) | 현재 BLC 드라이버의 내부 변수를 출력하는 예제입니다. |
| [**BLC-200_PositionWithConsole**](./BLC-200_PositionWithConsole) | 시리얼 통신을 통해 위치를 제어하는 예제입니다. |
| [**BLC-200_PositionWithSpeed**](./BLC-200_PositionWithSpeed) | 회전속도를 이용한 위치 제어 예제입니다. (위치, 속도제어) |
| [**BLC-200_PositionWithTime**](./BLC-200_PositionWithTime) | 위치 도달 시간을 이용한 위치 제어 예제입니다. (가감속 위치제어) |
| [**BLC-200_SpeedWithConsole**](./BLC-200_SpeedWithConsole) | 시리얼 통신을 통해 속도를 제어하는 예제입니다. |
| [**BLC-200_SpeedWithTime**](./BLC-200_SpeedWithTime) | 속도 도달 시간을 이용한 속도 제어 예제입니다. (가감속 속도제어) |
| [**BLC-200_IDSetting**](./BLC-200_IDSetting) | BLC 드라이버의 ID를 세팅하는 예제입니다. |
| [**BLC-200_LiveDemo**](./BLC-200_LiveDemo) | 테스트 구동 예제입니다. ([영상 참고](https://www.youtube.com/watch?v=O-PHxIAoegs&feature=emb_title)) |
| [**DMC-200_LiveDemo**](./DMC-200_LiveDemo) | DMC-200 + LM4075E 구동 예제입니다. ([영상 참고](https://youtu.be/hQbRMRIdBO4)) |

### API Guide
:star2: [API 가이드 보기](./BLC200.md) :star2:
