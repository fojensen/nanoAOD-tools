#include <TH1D.h>

double addOverflow(TH1D * h)
{
   const int n = h->GetNbinsX();
   double overflow = h->GetBinContent(n+1);
   if (!overflow) return 0.;
   std::cout << "Adding overflow to " << h->GetName() << std::endl;
   
   int nEntries = h->GetEntries();
   double overflowerror = h->GetBinError(n+1);
   double lastbin = h->GetBinContent(n);
   double lastbinerror = h->GetBinError(n);

   std::cout << "   input: " << std::endl;
   std::cout << "      GetEntries() =  " << nEntries <<  std::endl;
   std::cout << "      GetBinContent(n+1) = " << overflow << " +- " << overflowerror << std::endl;
   std::cout << "      GetBinContent(n) = " << lastbin << " +- " << lastbinerror << std::endl;

   h->AddBinContent(n, overflow);
   //h->Fill(h->GetBinCenter(n), overflow); //wrong, 1 fill can potentially have a huge weight
   h->SetBinContent(n+1, 0.);
   h->SetBinError(n+1, 0.);
   h->SetEntries(nEntries);
  
   nEntries = h->GetEntries(); 
   overflow = h->GetBinContent(n+1); 
   overflowerror = h->GetBinError(n+1);
   lastbin = h->GetBinContent(n);
   lastbinerror = h->GetBinError(n);

   std::cout << "   output: " << std::endl;
   std::cout << "      GetEntries() =  " << nEntries <<  std::endl;
   std::cout << "      GetBinContent(n+1) = " << overflow << " +- " << overflowerror << std::endl;
   std::cout << "      GetBinContent(n) = " << lastbin << " +- " << lastbinerror << std::endl;

   return overflow;
}

