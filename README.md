## Add Sliding Effect

![2022-01-13 16 21 20](https://user-images.githubusercontent.com/68891716/149284222-7197eaf2-3898-4cb9-be0f-3b0494035798.gif)


------
## Issue Closed

- ###### 벽에 근접, 사선방향으로 바라보면 텍스쳐가 깨짐

	![image](https://user-images.githubusercontent.com/68891716/149085919-8413facd-2ee3-4d8f-be37-c9a852d38d8f.png)

	- <u>drawing length > **screenHeight**</u> 인 경우인 듯.

------





![image (1)](https://user-images.githubusercontent.com/68891716/149085929-db4b3818-7d9f-4778-ac08-45058e8ca3d5.png)


1. ~~texture in front of a player~~
2. ~~collision detection~~ (temporary)
3. perspective

- 기존 **start y**, **end y** 가 화면범위 밖일 경우 각 <u>0, screenHeight 으로 trunc</u> 해주었으나, draw length, start, end y 를 이용해 texture 의 포지션을 계산하기 때문에 적합하지 않음
	- trunc 없이 **raw**한 y 의 범위를 texture 를 계산에 이용하되, **이미지버퍼**에 넣어줄때엔 **화면범위 밖의 y 는 스킵**하도록 처리

