# 복합센서를 활용한 피부 진단 관리 시스템
   * 팀명 : 라이온 피부 구하기 
   * 제품/서비스명(브랜드) : 허스트(Hubble Skin Telescope)
    
   <br/>
   <br/> 
    
    
프로젝트 개요
---  
   * 자신의 피부를 육안으로만 확인해서는 자세히 알 수 없으며
이로 인하여 피부에 맞는 화장품 선택에 어려움을 겪을 수 있다.
피부 상태를 이미지로 분석해주는 어플리케이션이 있지만 한계가 있다.
이에 본 프로젝트에서는 센서를 통해 피부 데이터를 읽어 피부 상태를 분석해주고
이에 따른 맞춤 솔루션을 제공하는 어플리케이션을 제작하고자 한다.
세부적으로는 육안으로 확인하기 어려운 유수분 밸런스, 피부 온도 등을 측정하고
입력된 데이터를 분석하여 맞춤 대응 방법을 제공한다.
또한 프로그램을 반복하여 사용했을 경우 사용자에게 피부 상태 변화 과정을 한눈에 볼 수 있도록 해준다
   <br/>  
   <br/> 
  
해결 방법
---  
   * DB의 데이터와 입력데이터를 비교하여 유수분 밸런스, 피부온도 등 피부의 전반적인 상태를 진단한다.
   <br/> 
   <br/> 
머신러닝 처리 계획:
CNN알고리즘을 이용하여 피부 이미지를 머신 러닝 처리 예정. 
처리 결과 피부의 건강 상태를 얻게 된다. 데이터 셋이 부족해 허스트를 통해 데이터를 먼저 모으고 보다 많은 데이터가 축적되면 정확도가 올라가게 될것이다.

기대효과
---  
   *  사용자 측면: 고가의 피부 클리닉 방문 없이 피부 관리가 가능하다. 
   *  기업적 측면: 피부진단을 하면서 얻은 빅데이터를 바탕으로 수익을 창출할 수도 있을 것이다(화장품 회사, 제약사 등등)
   <br/> 
   <br/> 
  
  
서비스 구성도
---
![005](https://user-images.githubusercontent.com/57625947/81494708-e7a90000-92e5-11ea-8ab2-33f7b52f2359.png)
  
<br/>
  
  
예상 시스템 구성도
---
![005](https://user-images.githubusercontent.com/57625947/80898825-287fa280-8d43-11ea-8207-7a84ca1560e9.JPG)


 <br/> 
 <br/> 
 <br/> 
 

<img src="img/diagram.png">

  <br/> 
  <br/> 

아두이노 연결
---  
   <img src="img/wiring.png">
   <br/>
   <br/> 

아두이노 핵심 코드
---  
   ``` c
   #include <ESP8266WiFi.h>
   #include <Wire.h>
   #include <Adafruit_MLX90614.h>

   Adafruit_MLX90614 mlx = Adafruit_MLX90614();
   WiFiClient client;

   void setup() {
      Serial.begin(115200);
      delay(10);
      mlx.begin();  
      WiFi.begin(ssid, password);

      ...
   }

   void loop() {
      float at = mlx.readAmbientTempC();
      float ot = mlx.readObjectTempC();
  
      if (isnan(at) || isnan(ot)) {
         Serial.println("Failed to read from sensor!");
         return;
      }

      if (client.connect(server,80)) {
         String postStr = ;
         ...
      }
      client.stop(); 
   }
   ```
  

데이터베이스 스키마
---  
   <img src="img/user_table.png">
   <img src="img/skin_temp_table.png">
   <img src="img/skin_image_table.png">
   <br/>
   <br/> 
   
   
Teams
---  
  
  
오정학(팀장)
   <br/>
<img src="https://user-images.githubusercontent.com/57625947/79041832-df4d9e80-7c2d-11ea-9a01-7f89f9e6ab30.png" width="150">
```
 *  역할 : 머신러닝 모듈 제작
```

   <br/>  
   <br/>     
   
성진호(Committer)
   <br/>
<img src="https://user-images.githubusercontent.com/57625947/79041833-e1aff880-7c2d-11ea-97cf-d7749775f55c.png" width="120">
```
 *  역할 : 웹서버 구축, UI/UX 디자인, 웹페이지 제작 
```

   <br/>  
   <br/>

강수연
   <br/>
<img src="https://user-images.githubusercontent.com/57625947/79041836-e4125280-7c2d-11ea-9ec5-28617e53fd63.jpg" width="120">
```
 *  역할 : 센서로 데이터 수집후 전송담당, 케이스제작, DB 구축 
```
   <br/>  
   <br/>  
   
개발환경(언어)
---
  * 사용 도구 : Github, SLack
  * 데이터베이스 : MySQL
  * 웹서버 : HTML, CSS, JavaScript


   <br/>  
   
마일스톤
---  
    * 프로젝트 요구사항 분석, 관련기술 조사 : 04/12 ~ 04/25
    * 센서 작동 테스트 : 04/25 ~ 04/30
    * 데이터베이스 구축 : 04/25 ~ 06/07
    * 웹페이지 제작, UI/UX 디자인 : 04/25 ~ 06/07
    * 머신러닝 모듈 구축 : 04/25 ~ 06/07
    * 프로그램 테스트, 문제점 보안 : 06/08 ~ 06/14
    * Demo Day : 06/15
    
      
      
   <br/>  

기대효과
---  
   *  사용자 측면: 고가의 피부 클리닉 방문 없이 피부 관리가 가능하다. 
   *  기업적 측면: 피부진단을 하면서 얻은 빅데이터를 바탕으로 수익을 창출할 수도 있을 것이다(화장품 회사, 제약사 등등)
   <br/> 
   <br/> 



향후 일정 계획
---      
<img src="https://user-images.githubusercontent.com/57625947/80255484-f83b6280-86b7-11ea-8777-7ace131cf419.png" width="750">
  
