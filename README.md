## 🎨 커밋 컨벤션

일관된 커밋 메시지를 유지하기 위해 아래의 커밋 컨벤션을 사용합니다.  

각 커밋 타입은 **영문 대문자**로 시작

**첫 글자는 반드시 대문자**로 작성

커밋 메시지 뒤에는 **수정한 파일명을 괄호로 표기**

| 커밋 타입 | 설명 | 예시 |
| ------- | ---- | ---- |
| ✨ **Feat** | 새로운 기능 추가 | `Feat(main.cc): 기능 추가` |
| 🐛 **Fix** | 버그 수정 | `Fix(main.cc): 오류 수정` |
| 📄 **Docs** | 문서 수정 | `Docs(README.md): README 파일 수정` |
| 🎨 **Style** | 코드 포맷팅, 세미콜론 누락 등 코드 변경이 없는 경우 | `Style(avl_tree.h): 코드 포맷팅 수정` |
| ♻️ **Refactor** | 코드 리팩토링 | `Refactor(avl_tree.cc): 함수 구조 개선` |
| ✅ **Test** | 테스트 코드 추가 또는 리팩토링 | `Test(avl_tree_test.cc): 유닛 테스트 추가` |
| 📦 **Chore** | 빌드 업무 수정, 패키지 매니저 수정 등 production code와 무관한 변경 | `Chore(.gitignore): .gitignore 파일 수정` |
| 💬 **Comment** | 주석 추가 및 변경 | `Comment(main.cc): 함수 설명 주석 추가` |
| 🔥 **Remove** | 파일 또는 폴더 삭제 | `Remove(test1.cc): 불필요한 파일 삭제` |
| 🚚 **Rename** | 파일 또는 폴더명 수정 | `Rename(test2.cc): 폴더명 변경` |
