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

my $systTotvbs = 0.111;
my $systTotqqzz = 0.0915;
my $systTotggzz = 0.137;
my $systTotttz = 0.146;
my $systTotzx = 0.38;

my $filename = 'MCyields_tot_2016_VBSenr.txt';
open(my $fh, '>', $filename) or die "Could not open file '$filename' $!";

# Calculate the rates
# 2016 summed
foreach $line (@log) {
    if ($fl1 == 0) {
	@splitline = split(/\t/, $line);
	my $temp = $splitline[0]+$splitline[5]+$splitline[10];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        print $fh &restrict_num_decimal_digits($systTotvbs*$temp,2);
	print $fh " \& ";
	$temp = $splitline[1]+$splitline[6]+$splitline[11];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        print $fh &restrict_num_decimal_digits($systTotzx*$temp,2);
	print $fh " \& ";
        $temp = $splitline[2]+$splitline[7]+$splitline[12];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        print $fh &restrict_num_decimal_digits($systTotqqzz*$temp,2);
	print $fh " \& ";
        $temp = $splitline[3]+$splitline[8]+$splitline[13];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        print $fh &restrict_num_decimal_digits($systTotggzz*$temp,2);
	print $fh " \& ";
	$temp = $splitline[4]+$splitline[9]+$splitline[14];
	print $fh &restrict_num_decimal_digits($temp,2);
	print $fh " \$\\pm\$ ";
        print $fh &restrict_num_decimal_digits($systTotttz*$temp,2);
	print $fh " \& ";
	$fl1++;
    }
}

$fl1 = 0;
close $fh ;

$filename = 'MCyields_tot_2017_VBSenr.txt';
open(my $fh2, '>', $filename) or die "Could not open file '$filename' $!";

# 2017 summed
foreach $line (@log2) {
    if ($fl2 == 0) {
	@splitline = split(/\t/, $line);
	my $temp = $splitline[0]+$splitline[5]+$splitline[10];
	print $fh2 &restrict_num_decimal_digits($temp,2);
	print $fh2 " \$\\pm\$ ";
        print $fh2 &restrict_num_decimal_digits($systTotvbs*$temp,2);
	print $fh2 " \& ";
	$temp = $splitline[1]+$splitline[6]+$splitline[11];
	print $fh2 &restrict_num_decimal_digits($temp,2);
	print $fh2 " \$\\pm\$ ";
        print $fh2 &restrict_num_decimal_digits($systTotzx*$temp,2);
	print $fh2 " \& ";
        $temp = $splitline[2]+$splitline[7]+$splitline[12];
	print $fh2 &restrict_num_decimal_digits($temp,2);
	print $fh2 " \$\\pm\$ ";
        print $fh2 &restrict_num_decimal_digits($systTotqqzz*$temp,2);
	print $fh2 " \& ";
        $temp = $splitline[3]+$splitline[8]+$splitline[13];
	print $fh2 &restrict_num_decimal_digits($temp,2);
	print $fh2 " \$\\pm\$ ";
        print $fh2 &restrict_num_decimal_digits($systTotggzz*$temp,2);
	print $fh2 " \& ";
	$temp = $splitline[4]+$splitline[9]+$splitline[14];
	print $fh2 &restrict_num_decimal_digits($temp,2);
	print $fh2 " \$\\pm\$ ";
        print $fh2 &restrict_num_decimal_digits($systTotttz*$temp,2);
	print $fh2 " \& ";
	$fl2++;
    }
}

$fl2 = 0;
close $fh2;

$filename = 'MCyields_tot_2018_VBSenr.txt';
open(my $fh3, '>', $filename) or die "Could not open file '$filename' $!";

# 2018 summed
foreach $line (@log3) {
    if ($fl3 == 0) {
	@splitline = split(/\t/, $line);
	my $temp = $splitline[0]+$splitline[5]+$splitline[10];
	print $fh3 &restrict_num_decimal_digits($temp,2);
	print $fh3 " \$\\pm\$ ";
        print $fh3 &restrict_num_decimal_digits($systTotvbs*$temp,2);
	print $fh3 " \& ";
	$temp = $splitline[1]+$splitline[6]+$splitline[11];
	print $fh3 &restrict_num_decimal_digits($temp,2);
	print $fh3 " \$\\pm\$ ";
        print $fh3 &restrict_num_decimal_digits($systTotzx*$temp,2);
	print $fh3 " \& ";
        $temp = $splitline[2]+$splitline[7]+$splitline[12];
	print $fh3 &restrict_num_decimal_digits($temp,2);
	print $fh3 " \$\\pm\$ ";
        print $fh3 &restrict_num_decimal_digits($systTotqqzz*$temp,2);
	print $fh3 " \& ";
        $temp = $splitline[3]+$splitline[8]+$splitline[13];
	print $fh3 &restrict_num_decimal_digits($temp,2);
	print $fh3 " \$\\pm\$ ";
        print $fh3 &restrict_num_decimal_digits($systTotggzz*$temp,2);
	print $fh3 " \& ";
	$temp = $splitline[4]+$splitline[9]+$splitline[14];
	print $fh3 &restrict_num_decimal_digits($temp,2);
	print $fh3 " \$\\pm\$ ";
        print $fh3 &restrict_num_decimal_digits($systTotttz*$temp,2);
	print $fh3 " \& ";
	$fl3++;
    }
}

$fl3 = 0;
close $fh3;

my $filename = 'MCyields_tot_all_VBSenr.txt';
open(my $fh4, '>', $filename) or die "Could not open file '$filename' $!";

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
			print $fh4 &restrict_num_decimal_digits($temp,2);
			print $fh4 " \$\\pm\$ ";
			print $fh4 &restrict_num_decimal_digits($systTotvbs*$temp,2);
			print $fh4 " \& ";
			$temp = $splitline[1]+$splitline[6]+$splitline[11]+$splitline2[1]+$splitline2[6]+$splitline2[11]+$splitline3[1]+$splitline3[6]+$splitline3[11];
			print $fh4 &restrict_num_decimal_digits($temp,2);
			print $fh4 " \$\\pm\$ ";
			print $fh4 &restrict_num_decimal_digits($systTotzx*$temp,2);
			print $fh4 " \& ";
			$temp = $splitline[2]+$splitline[7]+$splitline[12]+$splitline2[2]+$splitline2[7]+$splitline2[12]+$splitline3[2]+$splitline3[7]+$splitline3[12];
			print $fh4 &restrict_num_decimal_digits($temp,2);
			print $fh4 " \$\\pm\$ ";
			print $fh4 &restrict_num_decimal_digits($systTotqqzz*$temp,2);
			print $fh4 " \& ";
			$temp = $splitline[3]+$splitline[8]+$splitline[13]+$splitline2[3]+$splitline2[8]+$splitline2[13]+$splitline3[3]+$splitline3[8]+$splitline3[13];
			print $fh4 &restrict_num_decimal_digits($temp,2);
			print $fh4 " \$\\pm\$ ";
			print $fh4 &restrict_num_decimal_digits($systTotggzz*$temp,2);
			print $fh4 " \& ";
			$temp = $splitline[4]+$splitline[9]+$splitline[14]+$splitline2[4]+$splitline2[9]+$splitline2[14]+$splitline3[4]+$splitline3[9]+$splitline3[14];
			print $fh4 &restrict_num_decimal_digits($temp,2);
			print $fh4 " \$\\pm\$ ";
			print $fh4 &restrict_num_decimal_digits($systTotttz*$temp,2);
			print $fh4 " \& ";
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
