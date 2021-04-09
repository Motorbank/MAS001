### SBD-14

SBD-14 계열의 모터 드라이버를 연동하는 예제입니다. 자세한 내용은 **예제** 파일을 참고하시기 바랍니다.

### 쉴드 연결
SBD-14 모터 드라이버와 MAS-001 쉴드는 다음과 같이 연결됩니다. (***통신의 안정성을 위해 D+ 와 D-는 Twisted Pair로 연결하시기 바랍니다.***)

| SBD-14 | MAS-001 |
|:-----------:|:-----------:|
| TX1/A | D+ |
| RX1/B | D- |
| GND | GND |

### 예제

| Example | Description  |
|-----------|----------------------|
| [**SBD-14_DeviceScanning**](./SBD-14_DeviceScanning) | 현재 RS485로 연결된 SBD-14 드라이버들을 스캔하는 예제입니다. |
| [**SBD-14_DeviceSetting**](./SBD-14_DeviceSetting) | SBD-14 드라이버의 ID와 속도를 세팅하는 예제입니다. |
| [**SBD-14_MovePosition**](./SBD-14_MovePosition) | 위치 모드 구동 예제입니다. ([참고영상](https://youtu.be/nZYw-mWcKN0)) |
| [**SBD-14_MoveSpeed**](./SBD-14_MoveSpeed) | 속도 모드 구동 예제입니다. ([참고영상](https://youtu.be/AoSqB7c0BKc))|

### API Guide
:star2: [API 가이드 보기](./SBD14.md) :star2:
