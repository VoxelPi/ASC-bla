#include <iostream>

#include <vector.h>
#include <matrix.h>

namespace bla = bla;


int main()
{
  size_t n = 5;
  bla::Vector<double> x(n), y(n);

  for (size_t i = 0; i < x.Size(); i++)
    {
      x(i) = i;
      y(i) = 10;
    }

  bla::Vector<double> z = x+y;
  
  std::cout << "x+y = " << z << std::endl;


  bla::Vector<double> v(3);
  v(0) = 1.0;
  v(1) = 2.0;
  v(2) = 3.0;

  bla::Matrix<double, bla::RowMajor> A(2, 3);
  A(0, 0) = 0.0;
  A(0, 1) = 1.0;
  A(0, 2) = 2.0;
  A(1, 0) = 1.0;
  A(1, 1) = 0.0;
  A(1, 2) = 3.0;

  auto result = A * v;

  std::cout << "A*v = " << result << std::endl;

  bla::Matrix<double, bla::RowMajor> B(2, 2);
  B(0, 0) = 1.0;
  B(0, 1) = -1.0;
  B(1, 0) = 2.0;
  B(1, 1) = -2.0;

  auto mmProduct = A * B;

  std::cout << mmProduct <<  std::endl;

  bla::Matrix<double, bla::RowMajor> M(3, 4);
  bla::Matrix<double, bla::RowMajor> M2 = M.transpose();
  print(M2);

}


