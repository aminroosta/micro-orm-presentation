template <int p, int i>
class check_prime {
  public:
      enum { prim = ( (p % i) && check_prime<p, i - 1>::prim  )  };
};

template <int p>
class check_prime<p, 1> {
  public:
      enum { prim = 1  };
};

template<int n>
class is_prime {
  public:
  enum {value = check_prime<n,n-1>::prim };
};

int main() {
  bool is_prime_17 = is_prime<17>::value;
  bool is_prime_20 = is_prime<20>::value;
}
