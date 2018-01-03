﻿/*--------------
Sandy Bridge CPU를 출시하면서 AVX(Advanced Vector Extensions)가 추가 되었다.
AVX는 SIMD의 가장 최신 기술로 한 번에 256bit 데이터를 처리할 수 있다. 
따라서 기존의 128bit 데이터를 처리하는 SSE2에 비해 2배의 성능 향상을 기대할 수 있다.
다만 아직 256bit 데이터 처리에 정수형을 사용할 수 없고 실수형 데이터만 사용할 수 있다. (AVX2 부터 정수형 데이터도 추가되었다 )

구분							정수형 데이터			실수형 데이터			비고
256bit ymm 레지스터 사용		X						O						정수형은 AVX2 부터 사용 가능
3항 연산 사용				X						O						정수형은 xmm 레지스터 사용

실수형 연산에서 256bit ymm 레지스터 사용
- SSE는 실수형 연산에서 128bit xmm 레지스터 사용

3항 연산 기능 제공
- 기존 SSE는 2항 연산만 가능하여 source값을 저장하려면 추가적인 레지스터와 mov 명령어 필요

정수형 연산에서 256bit ymm 레지스터 사용 불가
- 정수형 연산에서 AVX 사용시 SSE와 동일하게 128bit xmm 레지스터 사용
- 정수형 연산에서 xmm 레지스터 3항 연산 사용 가능

실수형 연산에서는 SSE 대비 2배 크기의 레지스터를 사용하여 2배의 성능 향상을 얻을 수 있다.
정수형에서는 SSE와 같은 크기의 레지스터를 사용하므로 얻을 수 있는 성능의 차이는 없지만 3항 연산을 지원하여 코드의 양이 줄어드는 효과를 얻을 수 있다.

구분							SSE2					AVX
연산 방식					paddw, xmm0, xmm1		vpaddw xmm2, xmm0, xmm1
C 언어 방식 표현				b += a;					c = a + b;
소스 값을 보존해야 할 때		movdqu xmm2, xmm0		vpaddw xmm2, xmm0, xmm1
							paddw xmm2, xmm1		
CPU 연산						2번의 연산 명령 사용		1번의 연산 명령 사용

AVX 사용 환경
AVX를 사용하려면 다음과 같은 조건을 충족해야 한다.
CPU : 인텔 Sandy Bridge CPU
OS : Windows 7 Service Pack 1 SP1 이상
개발 도구 : Visual Studio 2010 SP 1 이상 또는 인텔 컴파일러 v12 이상
--------------*/
