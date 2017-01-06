var map;
var tabVille = [];
var tabNomVilles = [];

var longitude;
var lagitude;

var marker;

$(document).ready(function(){

  	lookingIntoJSON();//Utile pour initialiser les données pour le auto-complete.

	$("#affichageVille").hide(); //On cache le nom de la ville actuelle comme demander dans les requis.

	initMap(); //Initialisation de la map de Google.

	cacherPartieAnglaise();

	$( "#boutonFrancais" ).click(cacherPartieAnglaise); //Action faite quand le bouton francais est appuyé.

	$( "#boutonAnglais" ).click(cacherPartieFrancaise);//Action faite quand le bouton Anglais est appuyé.

	$( "#frenchButton" ).click(cacherPartieAnglaise);//Action faite quand le bouton french est appuyé.

	$( "#englishButton" ).click(cacherPartieFrancaise);//Action faite quand le bouton english est appuyé.

	$( "#inputNomVille" ).autocomplete({
		  source: tabNomVilles,
      select:function(e, data){//Lorsque un élément de la liste d'autocomplete est sélectionné,
        ///console.log(data.item.value);
        $( "#inputNomVille" ).val(data.item.value);//il devient le nouveau texte dans le input et
        settingLatLong();// les coordonnées lat,long sont mise a jour.
      }
		});
});

//Fonction qui sert a désactiver la partie anglaise du HTML
function cacherPartieAnglaise(){
        $("#english").hide();
        $( "#français" ).show();
        $("#boutonFrancais").attr("disabled", true);
        $("#villeFrancais").show();
        $("#villeAnglais").hide();
    }


//Fonction qui sert a désactiver la partie francaise du HTML
function cacherPartieFrancaise(){
  $( "#français" ).hide();
  $( "#english" ).show();
  $("#englishButton").attr("disabled", true);
  $("#villeAnglais").show();
  $("#villeFrancais").hide();
}

//Fonction qui sert a initialiser la map du HTML.
function initMap() {
  map = new google.maps.Map(document.getElementById('googleMap'), {
    center: {lat: 45.5, lng: -73.550003},
    zoom: 8
  });

  marker = new google.maps.Marker({
    position: {lat: 45.5, lng: -73.550003},
    map: map,
    //title: 'Hello World!'
  });
  map.setZoom(10);
}

//Fonction qui sert a initialise les valeurs pour l'auto-complet dans un tableau.
function lookingIntoJSON(){
  $.getJSON("villes.json", function(data) {
    tabVille = data;
    if(data[0] == $( "#inputNomVille" ).val()[0])
    $.map(data,function(villes, nom){
      tabNomVilles.push(nom);
    })
  });
  settingLatLong();
}

//Fonction qui met a jour les coordonnes du marker et de la map.

function settingLatLong(){

      ///console.log("input : " +$( "#inputNomVille" ).val());
    //On va voir dans le document JSON pour comparer avec l'entrée de l'utilisateur.
    $.getJSON("villes.json", function(data) {
    $.map(data,function(villes, nom){
    //Lorsque l'entrée de l'utilisateur correspond à une ville dans la liste JSON, on récupére ses coordonnées.
      if($( "#inputNomVille" ).val() == nom){
        ///console.log(tabVille[nom].lat);
        ///console.log(tabVille[nom].lon);
        longitude = tabVille[nom].lon;
        lagitude = tabVille[nom].lat
        map.setCenter({lat: lagitude, lng: longitude}); 
        marker.setPosition({lat: lagitude, lng: longitude});
       
       //Sert à afficher le nom de la ville au dessus de la map.
        $("#nomVille").text(nom);
        //Montre le texte de la ville au dessus de la map.
        $("#affichageVille").show();
      }
    })
  });
}