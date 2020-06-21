# 온도센서를 활용한 만성통증 조기 진단 시스템
   * 팀명 : 라이온 피부 구하기 
   * 제품/서비스명(브랜드) : 허스트(Hubble Skin Telescope)
    
   <br/>
   <br/> 
    
    
프로젝트 개요
---  
   * 건강 보험 심사 평가원에 따르면 국내 대상포진 환자는 꾸준히 증가하고 있다.
   최근 의료기기 시장의 주요 트랜드를 보면 가정에서 스스로 관리가 가능한 의료기기 시장이
   크게 성장하고 있는데 이에 본 프로젝트에서는 이러한 사회적 배경에 맞춰 가정에서 편리하게
   사용할 수 있고 사용자의 피부 온도를 센서를 통해 읽어들여서 대상포진 후 신경통 조기 진단 및
   진행 정도를 분석하게 해주는 프로그램을 제작하고자 한다.
   <br/>  
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
   <br/> 
   <br/>
   <br/> 
기대효과
---  
   *  사용자 측면: 고가의 피부 클리닉 방문 없이 피부 관리가 가능하다. 
   *  기업적 측면: 피부진단을 하면서 얻은 빅데이터를 바탕으로 수익을 창출할 수도 있을 것이다(화장품 회사, 제약사 등등)
   <br/> 
   <br/> 
  
예상 시스템 구성도
---
![01](https://user-images.githubusercontent.com/57625947/85220608-ee985780-b3e7-11ea-9c17-ebebeed11829.png)


 <br/> 
 <br/> 
 <br/> 
 

![02](https://user-images.githubusercontent.com/57625947/85220610-f657fc00-b3e7-11ea-9642-cf20b0c1a691.png)

  <br/> 
  <br/> 
  

데이터베이스 스키마
---  
   <img src="img/user_table.png">
   <img src="img/skin_temp_table.png">
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
    * 데이터베이스 구축 : 04/25 ~ 06/14
    * 웹페이지 제작, UI/UX 디자인 : 04/25 ~ 06/14
    * 머신러닝 모듈 구축 : 04/25 ~ 06/14
    * 프로그램 테스트, 문제점 보안 : 06/15 ~ 06/21
    * Demo Day : 06/22
    
      
      
   <br/>  
         
향후 일정 계획
---      
![03](https://user-images.githubusercontent.com/57625947/85220613-fbb54680-b3e7-11ea-9f41-67c93d4ef488.png)

  
