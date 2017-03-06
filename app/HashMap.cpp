#include <iostream>
#include "HashMap.hpp"


// KEVIN WANG 23797282


namespace
{
	unsigned int defaultHashFunc(const std::string& s)
	{
		int hash = 0;
		int num = 97;
		for( int x = 0; x<s.length(); x++)
		{
			hash = (hash*num) + s[x];
		}
		return hash;
	}
}


//Constructor
HashMap::HashMap()
	: hasher{defaultHashFunc},buckets{ new Node* [initialBucketCount]()}, bucketSize{0}, bucketCap{initialBucketCount}, totalPairs{0}, rehashing{false}
{

}
//Constructor w/ hasher function
HashMap::HashMap(HashFunction hasher)
	: hasher{hasher}, buckets{ new Node*[initialBucketCount]()}, bucketSize{0}, bucketCap{initialBucketCount}, totalPairs{0}, rehashing{false}
{

}

//CopyConstructor
HashMap::HashMap( const HashMap& hm )
	: hasher{hm.hasher}, buckets { new Node*[hm.bucketCap]()}, bucketSize{hm.bucketSize}, bucketCap{hm.bucketCap}, totalPairs{hm.totalPairs}, rehashing{hm.rehashing}
{
	hashMapCopy(buckets, hm.buckets, hm.bucketCap, hm.bucketCap, hm.rehashing);
}

//Destructor
HashMap::~HashMap()
{
	for(int x = 0; x<bucketCap; x++)
	{
		while(buckets[x])
		{
			Node* old = buckets[x];
			buckets[x] = buckets[x]->next;
			delete old;
		}
	}
	delete[] buckets;
}

void HashMap::deleteBuckets(Node**b, unsigned int cap)
{
	for(int x = 0; x<cap; x++)
	{
		while(b[x])
		{
			Node* old = b[x];
			buckets[x] = b[x]->next;
			delete old;
		}
	}
	delete[] b;
}

void HashMap::printBuckets( Node** b, unsigned int cap) //only prints out usernames
{
	for( int x = 0; x<cap; x++)
    {
    	if(b[x]==nullptr)
    		std::cout<<x<<":";
    	else
    	{
	    	Node* current = b[x]->next;
	    	while(current !=nullptr)
	    	{
	    		current = current->next;
	    	}
	    }
   	}	
}

bool HashMap::bucketIsEmpty(Node** b, unsigned int index)
{
	return b[index] == nullptr;
}

HashMap::Node* HashMap::findTail(Node* n)
{
	Node* temp = n;
	while(true)
	{
		if( temp->next == nullptr )
			return temp;
		else
			temp = temp->next;
	}
}


void HashMap::hashMapCopy( Node** target, Node** source, unsigned int cap, unsigned int newCap, bool rehash)
{
	rehashing = rehash;
	if(rehashing ==true)
		bucketSize = 0;
   	//printBuckets(source, cap);
	for ( unsigned int x = 0; x< cap; x++)
	{
		if(source[x]!=nullptr)			// checks first element
		{
			Node* current = source[x];
			int index = hasher(current->key)%newCap;

			if(bucketIsEmpty(target,index) == true)
			{
				target[index] = new Node{current->key, current->value, nullptr};
				if(rehashing ==true)
				{
					bucketSize++;
				}
			}
			else 
			{
				Node* lastNode = findTail(target[index]);
				Node* temp = new Node{current->key, current->value, nullptr};
				lastNode->next = temp;
			}

			current= current->next;
			while(current != nullptr)			// checking linked list
			{				
				int index = hasher(current->key)%newCap;
				Node* temp = new Node{current->key,current->value,nullptr};
				current = current->next;

				if( bucketIsEmpty(target, index) == true )
				{
					target[index] = temp;
					if(rehashing ==true)
					{
						bucketSize++;
					}
				}
				else
				{
					Node* lastNode = findTail(target[index]);
					lastNode->next = temp;
				}
			} 
		}
		
	}
	rehashing = false;
}

HashMap& HashMap::operator=(const HashMap& hm)
{
	if( this != &hm )	
	{
		Node** newBuckets = new Node*[hm.bucketCap]();
		hashMapCopy(newBuckets, hm.buckets, hm.bucketCap, hm.bucketCap, false);

		totalPairs = hm.totalPairs;
		bucketSize = hm.bucketSize;
		bucketCap = hm.bucketCap;
		hasher = hm.hasher;

		deleteBuckets(buckets, bucketCap);
		buckets = newBuckets;
	}
	return *this;
}

void HashMap::add(const std::string& key, const std::string& value)
{
	if( this->loadFactor() > 0.80)//
	{
		int newCap = bucketCap*2 +1;
		Node** newBuckets = new Node*[newCap]();
		hashMapCopy(newBuckets, buckets, bucketCap, newCap, true);

		deleteBuckets(buckets, bucketCap);
		bucketCap = newCap;
		buckets = newBuckets;
	}

	Node* newNode = new Node{key,value,nullptr};
	int index = hasher(newNode->key) % bucketCap;

	if(bucketIsEmpty(buckets, index) == true)
	{
		buckets[index]= newNode;
		bucketSize++;
	}
	else
	{
		Node* lastNode = findTail(buckets[index]);
		lastNode->next = newNode;
	}
	totalPairs++;
	//printBuckets(buckets, bucketCap);
}

void HashMap::remove(const std::string& s)
{
	bool finished = false;
	for( int x = 0; x<bucketCap; x++)
    {
    	if(finished == true)
    		break;
    	else if(buckets[x]==nullptr)
    		continue;
    	else
    	{
	    	Node* lastNode = buckets[x];
	    	Node* toRemove = buckets[x];
	    	if(lastNode->key == s)
	    	{
	    		buckets[x] = toRemove->next;
	    		delete toRemove;
	    		totalPairs = totalPairs-1;
	    		bucketSize = bucketSize -1;
	    		break;
	    	}
	    	toRemove = buckets[x]->next;
	    	while(toRemove != nullptr)
	    	{
	    		if(toRemove->key == s)
	    		{
	    			lastNode->next = toRemove->next;
	    			delete toRemove;
	    			finished = true;
	    			totalPairs = totalPairs -1;
	    			break;
	    		}
	    		else
	    		{
	    			lastNode = toRemove;
	    			toRemove = toRemove->next;
	    		}
	    	}
	    }
   	}	
   	//printBuckets(buckets, bucketCap);
}

bool HashMap::contains(const std::string& key) const
{
	for( int x = 0; x<bucketCap; x++)
    {
    	Node* current = buckets[x];
    	while(current)
    	{
    		if(current->key == key)
    			return true;
    		else
    			current = current->next;
    	}
    }
    return false;
}

std::string HashMap::value(const std::string& key) const
{
	for( int x = 0; x<bucketCap; x++)
    {
    	Node* current = buckets[x];
    	while(current)
    	{
    		if(current->key == key)
    			return current->value;
    		else
    			current = current->next;
    	}
    }
    return "";
}

unsigned int HashMap::size() const
{
	return totalPairs;
}

unsigned int HashMap::bucketCount() const
{
	return bucketSize;
}

double HashMap::loadFactor() const
{
	return double(totalPairs)/(double(bucketCap));
}

unsigned int HashMap::maxBucketSize() const
{
	unsigned int max=0;
	unsigned int sum=0;
	for( int x = 0; x<bucketCap; x++)
    {
    	Node* current = buckets[x];
    	while(current)
    	{
    		sum+=1;
    		current = current->next;
    	}
    	if(sum>=max)
    		max = sum;
    	sum = 0;
    }
    return max;

}

std::string* HashMap::getAllKeys() const
{
	if(totalPairs == 0)
		return NULL;
	std::string* result = new std::string[totalPairs];
	int y =0;
	for(int x =0; x<bucketCap; x++)
	{
		Node* temp = buckets[x];
		while(temp)
		{
			result[y]= temp->key;
			temp=temp->next;
			y++;
		}
	}
	return result;
}


