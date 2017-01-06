var app = angular.module("app",[]);

app.controller("seancesCtrl", function($scope, $http, $sce) {
		$http.get("seances.json").then(function(response) {
			$scope.seances = angular.forEach(response.data, function (seance, index, tableau) {
				tableau[index] = angular.forEach(seance, function(valeur, cle, tableau) {
					tableau[cle] = $sce.trustAsHtml(valeur);
				});
			});
		});
	});

app.controller('menuCtrl', function($scope, $http) {
    $http.get("menu.json").then(function(response) {
        $scope.menu = response.data.Navigation; //menu va directement contenir tout ce qu'il y a dans le fichier json.
    });
});

$( document ).ready(function(){
	$( ".print" ).click(function(){
		$( ".bottomClass" ).addClass( "hidden" );
		$( "#topmenu" ).addClass( "hidden" );
		$( "#lowMenu" ).addClass( "hidden" );
		$( ".print" ).addClass( "hidden" )
	});
});
