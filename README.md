## Issue Closed

- ###### 벽에 근접, 사선방향으로 바라보면 텍스쳐가 깨짐

	![image](/Users/shin/Desktop/Git/cub3D/image.png)![]()

	- <u>drawing length > **screenHeight**</u> 인 경우인 듯.

------





![image (1)](/Users/shin/Desktop/Git/cub3D/image (1)-1973187.png)



- 기존 **start y**, **end y** 가 화면범위 밖일 경우 각 <u>0, screenHeight 으로 trunc</u> 해주었으나, draw length, start, end y 를 이용해 texture 의 포지션을 계산하기 때문에 적합하지 않음
	- trunc 없이 **raw**한 y 의 범위를 texture 를 계산에 이용하되, **이미지버퍼**에 넣어줄때엔 **화면범위 밖의 y 는 스킵**하도록 처리

