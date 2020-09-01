### BLC-150

BLC-150 계열의 모터 드라이버를 연동하는 예제입니다. 자세한 내용은 **예제** 파일을 참고하시기 바랍니다. 해당 예제에 연동되는 드라이버는 다음과 같습니다.

* [BLC-150][1]
* [BLB-160][2]

[1]:https://www.motorbank.kr/goods/goods_view.php?goodsNo=1000009113
[2]:https://www.motorbank.kr/goods/goods_view.php?goodsNo=1000009614

### 쉴드 연결

| BLC-150 | MAS-001 |
|:-----------:|:----------------------:|
| 5V | - |
| ST/SP | D6 |
| PWM | - |
| CW/CCW | D5 |
| VR | A0 |
| GND | GND |

| BLB-160 | MAS-001 |
|:-----------:|:----------------------:|
| 5V | - |
| Vr(0-5V) | A0 |
| GND | GND |
| CW/CCW | D5 |
| BRAKE | D6 |
| GND | - |

### 예제

| Example | Description  |
|-----------|----------------------|
| [**BLC-150_Basic**](./BLC-150_Basic) | 기본 예제입니다. |