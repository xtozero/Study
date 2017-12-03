/*--------------
SIMD 연산에서 가장 시간이 소요되는 것은 메모리에서 레지스터로 데이터를 읽거나 쓰는 작업니다.
PC는 레지스터에서 메모리로 데이터를 쓸 때 재사용을 대비하여 캐시를 한번 거친다.
다시 사용하지 않는 데이터라면 캐시를 거치지 않고 바로 메모리에 쓰는 것이 빠르다.
재사용 하는 데이터의 경우에는 캐시를 사용하지 않으면 효율이 더 떨어질 수 있다.
Stream 함수는 반드시 16byte로 정렬되어 있어야 한다.


intrinsic 함수		SIMD 명령어		연산 방식
_mm_stream_pd		MOVNTPD			데이터 쓰기
_mm_stream_si128	MOVNTDQ			데이터 쓰기
_mm_stream_si32		MOVNTI			데이터 쓰기
_mm_stream_si64		MOVNTI			데이터 쓰기
_mm_clflush			CLFLUSH			Flush
_mm_lfence			LFENCE			동기화 보장
_mm_mfence			MFENCE			동기화 보장
--------------*/