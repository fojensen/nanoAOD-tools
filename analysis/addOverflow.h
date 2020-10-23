#include <iostream>
#include <TH1D.h>

double addOverflow(TH1D * h)
{
   const int n = h->GetNbinsX();
   const double o = h->GetBinContent(n+1);
   if (o>0.) {
      h->AddBinContent(n, o);
      h->SetBinContent(n+1, 0.);
      h->SetBinError(n+1, 0.);
      //std::cout << "overflow: " << h->GetName() << " " << o << std::endl;
   }
   return o;
}
