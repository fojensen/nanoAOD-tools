#include <TH1D.h>
#include <iostream>

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

   auto weights = h->GetSumw2();
   const double w2_2 = weights->At(n+1);
   const double w2_1 = weights->At(n);
   std::cout << "      sumw2 for overflow: " << w2_2 << std::endl;
   std::cout << "      sumw2 for last bin: " << w2_1 << std::endl;
   const double newerr = sqrt(w2_1+w2_2);

   h->AddBinContent(n, overflow);
   h->SetBinError(n, newerr);
   h->SetBinContent(n+1., 0.);
   h->SetBinError(n+1., 0.); 
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

void testOverflow()
{
   TH1D * h = new TH1D("h", ";;", 4, -0.5, 3.5);
   h->Fill(3., 0.7);
   h->Fill(3., 0.8);
   h->Fill(4., 0.9);
   addOverflow(h);
}

