/*--------------
void _mm_prefetch( char const* a, int sel )
제일 마지막 읽은 메모리 주소로부터 선택한 주소의 위치까지 캐시에 읽어들일 수 있는 힌트를 제공한다.

void _mm_stream_ps( float* p, __m128 a )
메모리에 데이터를 쓰게 될 때 레지스터에서 캐시 메모리를 거치지 않고 바로 쓰게 된다. 한 번만 쓰고 사용하지 않을 떄 효과적이며
메모리는 반드시 16byte로 정렬되어 있어야 한다.

void _mm_sfence(void)
여러 프로세스가 하나의 메모리에 접근하여 사용하게 될 때 동기화를 보장해준다. _mm_prefetch 와 _mm_stream_ps 사용시 같이 사용해야 한다.

intrinsic 함수		SIMD 명령어		연산 방식
_mm_prefetch		PREFETCH		읽기
_mm_stream_ps		MOVNTPS			쓰기
_mm_sfence			SFENCE			쓰기 동기화
--------------*/
