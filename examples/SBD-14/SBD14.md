# API Document

## SBD14_INSTANCE
```c
typedef struct{

  uint8_t id; // 모터 id

  {
    bool direction; // 모터 회전속도 세팅

    bool opt1_enable; // 포토 커플러 1 활성화 세팅
    bool opt1_stop_on_high; // 포토 커플러 1 정지 레벨 세팅

    bool opt2_enable; // 포토 커플러 2 활성화 세팅
    bool opt2_stop_on_high; // 포토 커플러 2 정지 레벨 세팅

    uint16_t speed; // 속도 세팅
    uint32_t position  // 위치 세팅

  } settings;

  {
    bool abnormal; // 비정상 표시
    bool opt1; // 포토 커플러 1 상태 표시
    bool opt2; // 포토 커플러 2 상태 표시
    uint16_t speed; // 속도 세팅 값 표시
  } state;

}SBD14_INSTANCE;
```

## API Functions
```c
bool set_ID(SBD14_INSTANCE *motor, uint8_t target_id);
```
* **description** : motor->id의 값을 가지는 드라이버를 target_id로 변경합니다.
* **arguments** :
  * motor : SBD14 모터 구조체
  * target_id : 타겟 아이디(0 ~ 127)
* **return**
  * true : 변경 성공
  * false : 변경 실패

```c
bool set_Speed(SBD14_INSTANCE *motor);
```
* **description** : motor->settings.speed [step/s]의 값으로 모터의 이동 속도 설정
* **arguments** :
  * motor : SBD14 모터 구조체
* **return**
  * true : 세팅 성공
  * false : 세팅 실패

```c
bool read_State(SBD14_INSTANCE *motor);
```
* **description** : motor->id의 값을 가지는 드라이버를 찾고, 해당 드라이버의 상태 값을 motor->state에 저장
* **arguments** :
  * motor : SBD14 모터 구조체
* **return**
  * true : 읽기 성공
  * false : 읽기 실패

```c
bool move_Speed(SBD14_INSTANCE *motor);
```
* **description** : 다음 변수를 이용해 motor->id의 값을 가지는 드라이버를 속도 제어 모드로 구동
  * motor->settings.direction :
    * true : 정방향
    * false : 역방향
  * motor->settings.opt1_enable :
    * true : 옵토 커플러 1 활성화
    * false : 옵토 커플러 1 비활성화
  * motor->settings.opt1_stop_on_high :
    * true : 옵토 커플러 1 하이 레벨 모터 정지
    * false : 옵토 커플러 1 로우 레벨 모터 정지
  * motor->settings.opt2_enable :
    * true : 옵토 커플러 2 활성화
    * false : 옵토 커플러 2 비활성화
  * motor->settings.opt2_stop_on_high :
    * true : 옵토 커플러 2 하이 레벨 모터 정지
    * false : 옵토 커플러 2 로우 레벨 모터 정지
* **arguments** :
  * motor : SBD14 모터 구조체
* **return**
  * true : 세팅 성공
  * false : 세팅 실패

```c
bool move_Position(SBD14_INSTANCE *motor);
```
* **description** : 다음 변수를 이용해 motor->id의 값을 가지는 드라이버를 위치 제어 모드로 구동
  * motor->settings.position : 타겟 위치 [step] (0 ~ 16,777,215)
  * motor->settings.direction :
    * true : 정방향
    * false : 역방향
  * motor->settings.opt1_enable :
    * true : 옵토 커플러 1 활성화
    * false : 옵토 커플러 1 비활성화
  * motor->settings.opt1_stop_on_high :
    * true : 옵토 커플러 1 하이 레벨 모터 정지
    * false : 옵토 커플러 1 로우 레벨 모터 정지
  * motor->settings.opt2_enable :
    * true : 옵토 커플러 2 활성화
    * false : 옵토 커플러 2 비활성화
  * motor->settings.opt2_stop_on_high :
    * true : 옵토 커플러 2 하이 레벨 모터 정지
    * false : 옵토 커플러 2 로우 레벨 모터 정지
* **arguments** :
  * motor : SBD14 모터 구조체
* **return**
  * true : 세팅 성공
  * false : 세팅 실패