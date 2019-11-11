foreach ll ( qqzz_Moriond ggzz_Moriond vbs_Moriond data) 
  echo "hadd -f ${ll}.root ${ll}_2016.root ${ll}_2017.root ${ll}_2018.root"
  hadd -f ${ll}.root ${ll}_2016.root ${ll}_2017.root ${ll}_2018.root
end
