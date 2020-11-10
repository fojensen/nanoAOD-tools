#include <iostream>
#include <TH1D.h>

double addOverflow(TH1D * h)
{
   const int n = h->GetNbinsX();
   const double o = h->GetBinContent(n+1);
   if (o>0.) {
      const double oerr = h->GetBinError(n+1);
      const double y = h->GetBinContent(n);
      const double yerr = h->GetBinError(n);
      h->SetBinContent(n+1, 0.);
      h->SetBinError(n+1, 0.);
      h->SetBinContent(n, o+y);
      const double err = sqrt((oerr*oerr)+(yerr*yerr));
      std::cout << "   overflow: " << o << " +- " << oerr << "; lastbin: " << y << " +- " << yerr << "; new lastbin: " << o+y << " +- " << err << std::endl;
      
   }
   return o;
}
