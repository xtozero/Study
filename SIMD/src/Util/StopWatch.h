#include <chrono>

using namespace std::chrono;

class CStopWatch
{
public:
	void Start( )
	{
		m_start = steady_clock::now( );
	}

	void End( )
	{
		m_end = steady_clock::now( );
	}

	template <typename Duration>
	typename Duration::rep GetDuration()
	{
		return duration_cast<Duration>( m_end - m_start ).count();
	}

public:
	time_point<steady_clock> m_start;
	time_point<steady_clock> m_end;
};