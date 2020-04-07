#!/usr/bin/perl

# Sum 2016-2017-2018 yields

$workdir = ".";

open(INFILE,"../../../../../CMSSW_8_0_26_patch1/src/vbs_analysis/4l_channel/MCyields_2016_VBSenr.txt") or die "cannot open file 2016";;
@log=<INFILE>;
close(INFILE);

open(INFILE2,"../../../../../CMSSW_8_0_26_patch1/src/vbs_analysis/4l_channel/MCyields_2017_VBSenr.txt") or die "cannot open file 2017";;
@log2=<INFILE2>;
close(INFILE2);

open(INFILE3,"../../../../../CMSSW_8_0_26_patch1/src/vbs_analysis/4l_channel/MCyields_2018_VBSenr.txt") or die "cannot open file 2018";;
@log3=<INFILE3>;
close(INFILE3);

my $fl1 = 0;
my $fl2 = 0;
my $fl3 = 0;

my $systTotvbs = 0.057;
my $systTotqqzz = 0.0915;
my $systTotggzz = 0.054;
my $systTotttz = 0.24;
my $systTotzx = 0.38;

my $systCorrvbs = 0.089;
my $systCorrqqzz = 0.112;
my $systCorrggzz = 0.137;
my $systCorrttz = 0.112;
my $systCorrzx = 0.;

my $filename = 'MCyields_tot_VBSenr.txt';
open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";

# Calculate the rates
# 2016 summed
foreach $line (@log) {
    if ($fl1 == 0) {
	@splitline = split(/\t/, $line);
	my $temp = $splitline[0]+$splitline[5]+$splitline[10];
        my $temp2 = $splitline[0]+$splitline[5]+$splitline[10];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotvbs*$temp;
        my $corrtemp = $systCorrvbs*$temp;        
        my $errtemp2 = $systTotvbs*$temp;
        my $corrtemp2 = $systCorrvbs*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[1]+$splitline[6]+$splitline[11];
        my $temp2 = $temp2+$splitline[1]+$splitline[6]+$splitline[11];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotzx*$temp;
        my $corrtemp = $systCorrzx*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotzx*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrzx*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[2]+$splitline[7]+$splitline[12];
        my $temp2 = $temp2+$splitline[2]+$splitline[7]+$splitline[12];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotqqzz*$temp;
        my $corrtemp = $systCorrqqzz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotqqzz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrqqzz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[3]+$splitline[8]+$splitline[13];
        my $temp2 = $temp2+$splitline[3]+$splitline[8]+$splitline[13];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotggzz*$temp;
        my $corrtemp = $systCorrggzz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotggzz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrggzz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = 1.1*($splitline[4]+$splitline[9]+$splitline[14]);
        my $temp2 = $temp2+1.1*($splitline[4]+$splitline[9]+$splitline[14]);
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotttz*$temp;
        my $corrtemp = $systCorrttz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotttz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrttz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	print $fh &restrict_num_decimal_digits($temp2,2);
	print $fh " \$\\pm\$ ";
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp2,$corrtemp2),2);
	print $fh " \&  \n ";
        $fl1++;
    }
}
 
$fl1 = 0;

# 2017 summed
foreach $line (@log2) {
    if ($fl2 == 0) {
	@splitline = split(/\t/, $line);
	my $temp = $splitline[0]+$splitline[5]+$splitline[10];
        my $temp2 = $splitline[0]+$splitline[5]+$splitline[10];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotvbs*$temp;
        my $corrtemp = $systCorrvbs*$temp;        
        my $errtemp2 = $systTotvbs*$temp;
        my $corrtemp2 = $systCorrvbs*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[1]+$splitline[6]+$splitline[11];
        my $temp2 = $temp2+$splitline[1]+$splitline[6]+$splitline[11];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotzx*$temp;
        my $corrtemp = $systCorrzx*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotzx*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrzx*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[2]+$splitline[7]+$splitline[12];
        my $temp2 = $temp2+$splitline[2]+$splitline[7]+$splitline[12];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotqqzz*$temp;
        my $corrtemp = $systCorrqqzz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotqqzz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrqqzz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[3]+$splitline[8]+$splitline[13];
        my $temp2 = $temp2+$splitline[3]+$splitline[8]+$splitline[13];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotggzz*$temp;
        my $corrtemp = $systCorrggzz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotggzz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrggzz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[4]+$splitline[9]+$splitline[14];
        my $temp2 = $temp2+$splitline[4]+$splitline[9]+$splitline[14];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotttz*$temp;
        my $corrtemp = $systCorrttz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotttz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrttz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	print $fh &restrict_num_decimal_digits($temp2,2);
	print $fh " \$\\pm\$ ";
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp2,$corrtemp2),2);
	print $fh " \&  \n ";
	$fl2++;
    }
}

$fl2 = 0;

# 2018 summed
foreach $line (@log3) {
    if ($fl3 == 0) {
	@splitline = split(/\t/, $line);
	my $temp = $splitline[0]+$splitline[5]+$splitline[10];
        my $temp2 = $splitline[0]+$splitline[5]+$splitline[10];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotvbs*$temp;
        my $corrtemp = $systCorrvbs*$temp;        
        my $errtemp2 = $systTotvbs*$temp;
        my $corrtemp2 = $systCorrvbs*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[1]+$splitline[6]+$splitline[11];
        my $temp2 = $temp2+$splitline[1]+$splitline[6]+$splitline[11];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotzx*$temp;
        my $corrtemp = $systCorrzx*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotzx*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrzx*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[2]+$splitline[7]+$splitline[12];
        my $temp2 = $temp2+$splitline[2]+$splitline[7]+$splitline[12];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotqqzz*$temp;
        my $corrtemp = $systCorrqqzz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotqqzz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrqqzz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[3]+$splitline[8]+$splitline[13];
        my $temp2 = $temp2+$splitline[3]+$splitline[8]+$splitline[13];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotggzz*$temp;
        my $corrtemp = $systCorrggzz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotggzz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrggzz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[4]+$splitline[9]+$splitline[14];
        my $temp2 = $temp2+$splitline[4]+$splitline[9]+$splitline[14];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotttz*$temp;
        my $corrtemp = $systCorrttz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotttz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrttz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	print $fh &restrict_num_decimal_digits($temp2,2);
	print $fh " \$\\pm\$ ";
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp2,$corrtemp2),2);
	print $fh " \&  \n ";

	$fl3++;
    }
}

$fl3 = 0;

foreach $line (@log) {
    if ($fl1 == 0) {
	foreach $line2 (@log2) {
	    if ($fl2 == 0) {
		foreach $line3 (@log3) {
		    if ($fl3 == 0) {
					
			@splitline = split(/\t/, $line);
			@splitline2 = split(/\t/, $line2);
			@splitline3 = split(/\t/, $line3);
		        
	my $temp = $splitline[0]+$splitline[5]+$splitline[10]+$splitline2[0]+$splitline2[5]+$splitline2[10]+$splitline3[0]+$splitline3[5]+$splitline3[10];
        my $temp2 = $splitline[0]+$splitline[5]+$splitline[10]+$splitline2[0]+$splitline2[5]+$splitline2[10]+$splitline3[0]+$splitline3[5]+$splitline3[10];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotvbs*$temp;
        my $corrtemp = $systCorrvbs*$temp;        
        my $errtemp2 = $systTotvbs*$temp;
        my $corrtemp2 = $systCorrvbs*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[1]+$splitline[6]+$splitline[11]+$splitline2[1]+$splitline2[6]+$splitline2[11]+$splitline3[1]+$splitline3[6]+$splitline3[11];
        my $temp2 = $temp2+$splitline[1]+$splitline[6]+$splitline[11]+$splitline2[1]+$splitline2[6]+$splitline2[11]+$splitline3[1]+$splitline3[6]+$splitline3[11];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotzx*$temp;
        my $corrtemp = $systCorrzx*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotzx*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrzx*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[2]+$splitline[7]+$splitline[12]+$splitline2[2]+$splitline2[7]+$splitline2[12]+$splitline3[2]+$splitline3[7]+$splitline3[12];
        my $temp2 = $temp2+$splitline[2]+$splitline[7]+$splitline[12]+$splitline2[2]+$splitline2[7]+$splitline2[12]+$splitline3[2]+$splitline3[7]+$splitline3[12];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotqqzz*$temp;
        my $corrtemp = $systCorrqqzz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotqqzz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrqqzz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = $splitline[3]+$splitline[8]+$splitline[13]+$splitline2[3]+$splitline2[8]+$splitline2[13]+$splitline3[3]+$splitline3[8]+$splitline3[13];
        my $temp2 = $temp2+$splitline[3]+$splitline[8]+$splitline[13]+$splitline2[3]+$splitline2[8]+$splitline2[13]+$splitline3[3]+$splitline3[8]+$splitline3[13];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotggzz*$temp;
        my $corrtemp = $systCorrggzz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotggzz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrggzz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	my $temp = 1.1*($splitline[4]+$splitline[9]+$splitline[14])+$splitline2[4]+$splitline2[9]+$splitline2[14]+$splitline3[4]+$splitline3[9]+$splitline3[14];
        my $temp2 = 1.1*($temp2+$splitline[4]+$splitline[9]+$splitline[14])+$splitline2[4]+$splitline2[9]+$splitline2[14]+$splitline3[4]+$splitline3[9]+$splitline3[14];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        my $errtemp = $systTotttz*$temp;
        my $corrtemp = $systCorrttz*$temp;        
        my $errtemp2 = &quadrature_sum($errtemp2,$systTotttz*$temp);        
        my $corrtemp2 = $corrtemp2+$systCorrttz*$temp;        
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp,$corrtemp),2);
	print $fh " \& ";
	print $fh &restrict_num_decimal_digits($temp2,2);
	print $fh " \$\\pm\$ ";
        print $fh &restrict_num_decimal_digits(&quadrature_sum($errtemp2,$corrtemp2),2);
	print $fh " \& ";

			$fl3++;
			

		    }
		}
		$fl2++;
		}
	}
	$fl1++;
    }
}

close $fh4;
print "done\n";

sub restrict_num_decimal_digits
{
  my $num=shift;#the number to work on
  my $digs_to_cut=shift;# the number of digits after 
		        # the decimal point to cut 
		        #(eg: $digs_to_cut=3 will leave 
	         	# two digits after the decimal point)

  if ($num=~/\d+\.(\d){$digs_to_cut,}/)
  {
    # there are $digs_to_cut or 
    # more digits after the decimal point
    $num=sprintf("%.".($digs_to_cut-1)."f", $num);
  }
  return $num;
}

sub quadrature_sum
{
  my $num=shift;#the number to work on
  my $sum=shift;#
  my $result = sqrt($num*$num+$sum*$sum); 
  return $result
}

