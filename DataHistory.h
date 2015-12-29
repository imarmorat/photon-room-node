class DataHistory
{
public:
	struct DataHistoryEntry
	{
		float min;
		float avg;
		float max;
		DataHistoryEntry(float value) { min = max = avg = value; }
	};
	
	DataHistory(int bucketInMin)
	{
		int nbEntries = 24 * 60 / bucketInMin;
		_bucketSizeInMin = bucketInMin;
		_entries = (DataHistoryEntry **)malloc(sizeof(DataHistoryEntry *) * nbEntries);
		_time = Time.now();
	}

	void Handle(float value)
	{
		bool isWithinCurrentBucket = _time + _bucketSizeInMin * 60 < Time.now();
		DataHistoryEntry* bucket;

		if (isWithinCurrentBucket)
		{
			bucket = _entries[_entriesCount];
		}
		else
		{
			_entries[++_entriesCount] = new DataHistoryEntry(value);
		}

		// update bucket info + others
		// todo
		bucket->min = value < bucket->min ? value : bucket->min;
		bucket->max = value > bucket->max ? value : bucket->max;
		bucket->avg = (bucket->avg * n + value) / (n + 1); // http://www.bennadel.com/blog/1627-create-a-running-average-without-storing-individual-values.htm

		// day min/max
		_dayMin = value < _dayMin ? value : _dayMin;
		_dayMax = value > _dayMax ? value : _dayMax;
	}

	int GetNbEntries() { return _entriesCount;  }
	DataHistoryEntry** GetEntries() { return _entries;  }

	void GetDayMax() { return _dayMax; }
	void GetDayMin() { return _dayAvg; }
	void GetDayAvg() { return _dayAvg; }

private:
	DataHistoryEntry** _entries;
	int _entriesCount = 0;
	float _dayMin, _dayAvg, _dayMax;
	unsigned long _time;
	int _bucketSizeInMin;
};