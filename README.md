# Final Project 

對於模板不良品質表達憤慨，所以就重新做一個吧  

目標：
- 更優秀的引擎：好用清晰簡單的API、不操作裸指針、不依賴引擎以外的程式
  - Bonus：平行化提高效能
- 使用ECS設計模式

依賴項：Allegro、spdlog、EnTT
避免重複工作，優先使用優秀的第三方庫

目標細節 - 引擎：  
提供的功能
- 簡易2d向量庫
- Engine封裝(包含視窗處理、迴圈處理、初始化工作)
- Scene封裝(Engine可以處理Scene)
- Text封裝
- Image封裝
- Sound封裝
