/*--------------
각 pack에 들어 있는 값을 형변환시킨다.

명명법
_mm_cvt : 형변환 intrinsic 함수임을 의미
ss : 32bit float 형 스칼라
ps : 32bit float 형 pack
pd : 64bit double 형 pack
si32 : 32bit 정수형 스칼라

intrinsic 함수		SIMD 명령어		연산 방식
_mm_cvtss_si32		CVTSS2SI		32bit 정수 1개로 변환
_mm_cvtss_si64		CVTSS2SI		64bit 정수 1개로 변환
_mm_cvtps_pi32		CVTPS2PI		32bit 정수 2개로 변환
_mm_cvttss_si32		CVTTSS2SI		32bit 정수 1개로 변환
_mm_cvttss_si64		CVTTSS2SI		64bit 정수 1개로 변환
_mm_cvttps_pi32		CVTTPS2PI		32bit 정수 2개로 변환
_mm_cvtsi32_ss		CVTSI2SS		32bit 정수를 실수로 변환
_mm_cvtsi64_ss		CVTSI2SS		64bit 정수를 실수로 변환
_mm_cvtpi32_ps		CVTTPI2PS		32bit 정수 2개를 실수로 변환
_mm_cvtpi16_ps		없음				16bit 정수 4개를 실수로 변환
_mm_cvtpu16_ps		없음				16bit 정수 4개를 실수로 변환
_mm_cvtpi8_ps		없음				8bit 정수 4개를 실수로 변환
_mm_cvtpu8_ps		없음				8bit 정수 4개를 실수로 변환
_mm_cvtpi32x2_ps	없음				32bit 정수 4개를 실수로 변환
_mm_cvtps_pi16		없음				실수를 16bit 정수 4개로 변환
_mm_cvtps_pi8		없음				실수를 8bit 정수 4개로 변환
_mm_cvtss_f32		없음				하위 위치 실수 한 개를 꺼내옴
--------------*/